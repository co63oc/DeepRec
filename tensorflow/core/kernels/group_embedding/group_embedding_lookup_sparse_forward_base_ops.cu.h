/* Copyright 2022 The DeepRec Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
=======================================================================*/

#if GOOGLE_CUDA

#include <cooperative_groups.h>
#include <cuda_runtime.h>

#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/kernels/fused_embedding/fused_embedding_common.cu.h"
#include "tensorflow/core/kernels/training_op_helpers.h"
#include "tensorflow/core/util/gpu_kernel_helper.h"
#include "tensorflow/stream_executor/stream_executor.h"

namespace tensorflow {

namespace {

template <typename TKey, typename TValue>
struct GroupEmbeddingForWardArgs {
  TValue* emb_variable_;
  TValue* emb_vector_;
  TValue* sp_weights_;
  TKey* sp_values_;
  int* offset_indices_;
  int nnz_;
  int emb_row_size_;
};

__global__ void SetToIntMaxSTG128(const int batch_size, int* values_offset) {
  const int thread_offset = 4 * (blockIdx.x * blockDim.x + threadIdx.x);
  const int int_max = 0x7fffffff;
  if (thread_offset + 4 < batch_size) {
    int4 four = make_int4(int_max, int_max, int_max, int_max);
    *((int4*)(values_offset + thread_offset)) = four;
  } else if (thread_offset < batch_size) {
    for (int i = thread_offset; i < batch_size; i++) {
      values_offset[i] = int_max;
    }
  }
}

__global__ void CalcPerElementRowOffset(const int batch_size, const int64_t nnz,
                                        const int64_t* indices,
                                        volatile int* values_offset) {
  const int thread_offset = blockIdx.x * blockDim.x + threadIdx.x;
  const int int_max = 0x7fffffff;
  if (thread_offset < int(nnz)) {
    const int64_t element_row = indices[thread_offset];
    atomicMin((int*)values_offset + int(element_row), thread_offset);
    __syncthreads();
    if (thread_offset < int(batch_size - 1)) {
      while (values_offset[thread_offset + 1] == int_max) {
      }
      const int compare = values_offset[thread_offset + 1];
      atomicMin((int*)values_offset + thread_offset, compare);
    }
  }
}

inline void launch_cal_per_element_row_offset(const int batch_size, int nnz,
                                              const int64_t* sp_indices,
                                              int* offset_indices,
                                              cudaStream_t stream) {
  static int threads = 1024;
  int blocks = (batch_size - 1) / threads + 1;

  SetToIntMaxSTG128<<<blocks, threads, 0, stream>>>(batch_size, offset_indices);

  blocks = (nnz - 1) / threads + 1;
  CalcPerElementRowOffset<<<blocks, threads, 0, stream>>>(
      batch_size, nnz, sp_indices, offset_indices);
}

template <typename TKey, typename TValue, Combiner combiner, int Tilesize>
__global__ void WeightedEmbeddingVarComputeFn(
    const int batch_size, const int dimension, const float max_norm,
    const int num_lookups, GroupEmbeddingForWardArgs<TKey, TValue>* args) {
  TValue l2_sum;

  const auto& block = cooperative_groups::this_thread_block();
  const auto& tile = cooperative_groups::tiled_partition<Tilesize>(block);
  // each block partition corresponding to one sample
  const int bid =
      block.group_index().x * tile.meta_group_size() + tile.meta_group_rank();
  // each thread corresponding to one element in the embedding vector
  const int tid = tile.thread_rank();

  if (bid < batch_size && tid < dimension) {
    for (int ev_id = 0; ev_id < num_lookups; ++ev_id) {
      int value_offset = args[ev_id].offset_indices_[bid];
      int feature_num;
      if (bid == (batch_size - 1)) {
        feature_num = args[ev_id].nnz_ - value_offset;
      } else {
        feature_num = args[ev_id].offset_indices_[bid + 1] - value_offset;
      }

      float out = 0.0f;

      // #pragma unroll
      for (int j = 0; j < feature_num; ++j) {
        int64_t feature_offset = (value_offset + j) * dimension;
        TValue sum = args[ev_id].emb_variable_[feature_offset + tid];
        TValue sp_weights = args[ev_id].sp_weights_[feature_offset + tid];
        if (max_norm >= 0.0) {
          if (tid == 0) {
            l2_sum = 0.0;
          }
          tile.shfl(l2_sum, 0);
          atomicAdd(&l2_sum, sum * sum);
          tile.sync();
          TValue l2_norm = sqrtf(l2_sum);
          if (l2_norm > max_norm) {
            sum *= max_norm / l2_norm;
          }
        }
        out += sum * sp_weights;
      }
      out = Combine<combiner>(out, feature_num);
      args[ev_id].emb_vector_[bid * dimension + tid] = out;
    }
  }
}

template <typename TKey, typename TValue, Combiner combiner, int Tilesize>
__global__ void WeightedVariableComputeFn(
    const int batch_size, const int emb_vec_size, const float max_norm,
    const int num_lookups, GroupEmbeddingForWardArgs<TKey, TValue>* args) {
  TValue l2_sum;
  const auto& block = cooperative_groups::this_thread_block();
  const auto& tile = cooperative_groups::tiled_partition<Tilesize>(block);
  // each block partition corresponding to one sample
  const int bid =
      block.group_index().x * tile.meta_group_size() + tile.meta_group_rank();
  // each thread corresponding to one element in the embedding vector
  const int tid = tile.thread_rank();

  if (bid < batch_size && tid < emb_vec_size) {
    for (int ev_id = 0; ev_id < num_lookups; ++ev_id) {
      int value_offset = args[ev_id].offset_indices_[bid];
      int feature_num;
      if (bid == (batch_size - 1)) {
        feature_num = args[ev_id].nnz_ - value_offset;
      } else {
        feature_num = args[ev_id].offset_indices_[bid + 1] - value_offset;
      }

      TValue out = 0.0f;

      const TValue* emb_variable = args[ev_id].emb_variable_;
      const int64_t emb_dim_limit = args[ev_id].emb_row_size_;
      // #pragma unroll
      for (int i = 0; i < feature_num; i++) {
        int indices = int(args[ev_id].sp_values_[value_offset + i]);
        TValue sp_weights = args[ev_id].sp_weights_[bid * emb_vec_size + tid];
        TValue emb_element = emb_variable[indices * emb_vec_size + tid];
        if (max_norm >= 0.0f) {
          // calc l2 norm of this emb row(per block) and compare with
          // max_norm.
          // if greater than max_norm, then clip every element with factor
          // max_norm / l2norm
          if (tid == 0) {
            l2_sum = 0.0f;
          }
          tile.shfl(l2_sum, 0);
          atomicAdd(&l2_sum, emb_element * emb_element);
          tile.sync();
          TValue l2_norm = sqrtf(l2_sum);
          if (l2_norm > max_norm) {
            emb_element *= max_norm / l2_norm;
          }
        }
        out += emb_element * sp_weights;
      }
      out = Combine<combiner>(out, feature_num);
      args[ev_id].emb_vector_[bid * emb_vec_size + tid] = out;
    }
  }
}

template <typename TKey, typename TValue, Combiner combiner, int Tilesize>
__global__ void EmbeddingVarComputeFn(
    const int batch_size, const int dimension, const float max_norm,
    const int num_lookups, GroupEmbeddingForWardArgs<TKey, TValue>* args) {
  TValue l2_sum;

  const auto& block = cooperative_groups::this_thread_block();
  const auto& tile = cooperative_groups::tiled_partition<Tilesize>(block);
  // each block partition corresponding to one sample
  const int bid =
      block.group_index().x * tile.meta_group_size() + tile.meta_group_rank();
  // each thread corresponding to one element in the embedding vector
  const int tid = tile.thread_rank();

  if (bid < batch_size && tid < dimension) {
    for (int ev_id = 0; ev_id < num_lookups; ++ev_id) {
      int value_offset = args[ev_id].offset_indices_[bid];
      int feature_num;
      if (bid == (batch_size - 1)) {
        feature_num = args[ev_id].nnz_ - value_offset;
      } else {
        feature_num = args[ev_id].offset_indices_[bid + 1] - value_offset;
      }
      TValue out = 0.0;

      // #pragma unroll
      for (int j = 0; j < feature_num; ++j) {
        int64_t feature_offset = (value_offset + j) * dimension;
        TValue sum = args[ev_id].emb_variable_[feature_offset + tid];
        if (max_norm >= 0.0) {
          if (tid == 0) {
            l2_sum = 0.0;
          }
          tile.shfl(l2_sum, 0);
          atomicAdd(&l2_sum, sum * sum);
          tile.sync();
          TValue l2_norm = sqrtf(l2_sum);
          if (l2_norm > max_norm) {
            sum *= max_norm / l2_norm;
          }
        }
        out += sum;
      }
      out = Combine<combiner>(out, feature_num);
      args[ev_id].emb_vector_[bid * dimension + tid] = out;
    }
  }
}

template <typename TKey, typename TValue, Combiner combiner, int Tilesize>
__global__ void VariableComputeFn(
    const int batch_size, const int emb_vec_size, const float max_norm,
    const int num_lookups, GroupEmbeddingForWardArgs<TKey, TValue>* args) {
  TValue l2_sum;
  const auto& block = cooperative_groups::this_thread_block();
  const auto& tile = cooperative_groups::tiled_partition<Tilesize>(block);
  // each block partition corresponding to one sample
  const int bid =
      block.group_index().x * tile.meta_group_size() + tile.meta_group_rank();
  // each thread corresponding to one element in the embedding vector
  const int tid = tile.thread_rank();

  if (bid < batch_size && tid < emb_vec_size) {
    for (int ev_id = 0; ev_id < num_lookups; ++ev_id) {
      int value_offset = args[ev_id].offset_indices_[bid];
      int feature_num;
      if (bid == (batch_size - 1)) {
        feature_num = args[ev_id].nnz_ - value_offset;
      } else {
        feature_num = args[ev_id].offset_indices_[bid + 1] - value_offset;
      }
      TValue out = 0.0f;

      const TValue* emb_variable = args[ev_id].emb_variable_;
      const int64_t emb_dim_limit = args[ev_id].emb_row_size_;
      // #pragma unroll
      for (int i = 0; i < feature_num; i++) {
        int indices = int(args[ev_id].sp_values_[value_offset + i]);
        TValue emb_element = emb_variable[indices * emb_vec_size + tid];
        // printf("indices is %d emb_element is %f\n", indices, emb_element);
        if (max_norm >= 0.0f) {
          // calc l2 norm of this emb row(per block) and compare with
          // max_norm.
          // if greater than max_norm, then clip every element with factor
          // max_norm / l2norm
          if (tid == 0) {
            l2_sum = 0.0f;
          }
          tile.shfl(l2_sum, 0);
          atomicAdd(&l2_sum, emb_element * emb_element);
          tile.sync();
          TValue l2_norm = sqrtf(l2_sum);
          if (l2_norm > max_norm) {
            emb_element *= max_norm / l2_norm;
          }
        }
        out += emb_element;
      }
      out = Combine<combiner>(out, feature_num);
      // printf("feature_num is %d value_offset is %d out is %f\n", feature_num,
      // value_offset, out);
      args[ev_id].emb_vector_[bid * emb_vec_size + tid] = out;
    }
  }
}

template <typename TKey, typename TValue, Combiner combiner>
__global__ void NormalEmbeddingVarComputeFn(
    const int batch_size, const int dimension, const float max_norm,
    const int num_lookups, GroupEmbeddingForWardArgs<TKey, TValue>* args) {
  __shared__ TValue l2_sum[1];

  const auto& block = cooperative_groups::this_thread_block();
  // each block partition corresponding to one sample
  const int bid = block.group_index().x;
  // each thread corresponding to one element in the embedding vector
  const int tid = block.thread_rank();

  if (bid < batch_size && tid < dimension) {
    for (int ev_id = 0; ev_id < num_lookups; ++ev_id) {
      int value_offset = args[ev_id].offset_indices_[bid];
      int feature_num;
      if (bid == (batch_size - 1)) {
        feature_num = args[ev_id].nnz_ - value_offset;
      } else {
        feature_num = args[ev_id].offset_indices_[bid + 1] - value_offset;
      }
      TValue out = 0.0;

      // #pragma unroll
      for (int j = 0; j < feature_num; ++j) {
        int64_t feature_offset = (value_offset + j) * dimension;
        TValue sum = args[ev_id].emb_variable_[feature_offset + tid];
        if (max_norm >= 0.0) {
          if (tid == 0) {
            l2_sum[0] = 0.0;
          }
          block.sync();
          atomicAdd(l2_sum, sum * sum);
          block.sync();
          TValue l2_norm = sqrtf(l2_sum[0]);
          if (l2_norm > max_norm) {
            sum *= max_norm / l2_norm;
          }
        }
        out += sum;
      }

      out = Combine<combiner>(out, feature_num);
      args[ev_id].emb_vector_[bid * dimension + tid] = out;
    }
  }
}

template <typename TKey, typename TValue, Combiner combiner>
__global__ void NormalVariableComputeFn(
    const int batch_size, const int emb_vec_size, const float max_norm,
    const int num_lookups, GroupEmbeddingForWardArgs<TKey, TValue>* args) {
  __shared__ TValue l2_sum[1];
  const auto& block = cooperative_groups::this_thread_block();
  // each block partition corresponding to one sample
  const int bid = block.group_index().x;
  // each thread corresponding to one element in the embedding vector
  const int tid = block.thread_rank();

  if (bid < batch_size && tid < emb_vec_size) {
    for (int ev_id = 0; ev_id < num_lookups; ++ev_id) {
      int value_offset = args[ev_id].offset_indices_[bid];
      int feature_num;
      if (bid == (batch_size - 1)) {
        feature_num = args[ev_id].nnz_ - value_offset;
      } else {
        feature_num = args[ev_id].offset_indices_[bid + 1] - value_offset;
      }
      TValue out = 0.0f;

      const TValue* emb_variable = args[ev_id].emb_variable_;
      const int64_t emb_dim_limit = args[ev_id].emb_row_size_;
      // #pragma unroll
      for (int i = 0; i < feature_num; i++) {
        int indices = int(args[ev_id].sp_values_[value_offset + i]);
        TValue emb_element = emb_variable[indices * emb_vec_size + tid];
        // printf("indices is %d emb_element is %f\n", indices, emb_element);
        if (max_norm >= 0.0f) {
          // calc l2 norm of this emb row(per block) and compare with
          // max_norm.
          // if greater than max_norm, then clip every element with factor
          // max_norm / l2norm
          if (tid == 0) {
            l2_sum[0] = 0.0f;
          }
          block.sync();
          atomicAdd(l2_sum, emb_element * emb_element);
          block.sync();
          TValue l2_norm = sqrtf(l2_sum[0]);
          if (l2_norm > max_norm) {
            emb_element *= max_norm / l2_norm;
          }
        }
        out += emb_element;
      }
      out = Combine<combiner>(out, feature_num);
      // printf("feature_num is %d value_offset is %d out is %f\n", feature_num,
      // value_offset, out);
      args[ev_id].emb_vector_[bid * emb_vec_size + tid] = out;
    }
  }
}

template <typename TKey, typename TValue, Combiner combiner>
__global__ void NormalWeightedEmbeddingVarComputeFn(
    const int batch_size, const int dimension, const float max_norm,
    const int num_lookups, GroupEmbeddingForWardArgs<TKey, TValue>* args) {
  __shared__ TValue l2_sum[1];

  const auto& block = cooperative_groups::this_thread_block();
  // each block partition corresponding to one sample
  const int bid = block.group_index().x;
  // each thread corresponding to one element in the embedding vector
  const int tid = block.thread_rank();

  if (bid < batch_size && tid < dimension) {
    for (int ev_id = 0; ev_id < num_lookups; ++ev_id) {
      int value_offset = args[ev_id].offset_indices_[bid];
      int feature_num;
      if (bid == (batch_size - 1)) {
        feature_num = args[ev_id].nnz_ - value_offset;
      } else {
        feature_num = args[ev_id].offset_indices_[bid + 1] - value_offset;
      }
      TValue out = 0.0;

      // #pragma unroll
      for (int j = 0; j < feature_num; ++j) {
        int64_t feature_offset = (value_offset + j) * dimension;
        TValue sum = args[ev_id].emb_variable_[feature_offset + tid];
        TValue sp_weights =
            args[ev_id].sp_weights_[feature_offset + tid];
        if (max_norm >= 0.0) {
          if (tid == 0) {
            l2_sum[0] = 0.0;
          }
          block.sync();
          atomicAdd(l2_sum, sum * sum);
          block.sync();
          TValue l2_norm = sqrtf(l2_sum[0]);
          if (l2_norm > max_norm) {
            sum *= max_norm / l2_norm;
          }
        }
        out += sum * sp_weights;
      }

      out = Combine<combiner>(out, feature_num);
      args[ev_id].emb_vector_[bid * dimension + tid] = out;
    }
  }
}

template <typename TKey, typename TValue, Combiner combiner>
__global__ void NormalWeightedVariableComputeFn(
    const int batch_size, const int emb_vec_size, const float max_norm,
    const int num_lookups, GroupEmbeddingForWardArgs<TKey, TValue>* args) {
  __shared__ TValue l2_sum[1];
  const auto& block = cooperative_groups::this_thread_block();
  // each block partition corresponding to one sample
  const int bid = block.group_index().x;
  // each thread corresponding to one element in the embedding vector
  const int tid = block.thread_rank();

  if (bid < batch_size && tid < emb_vec_size) {
    for (int ev_id = 0; ev_id < num_lookups; ++ev_id) {
      int value_offset = args[ev_id].offset_indices_[bid];
      int feature_num;
      if (bid == (batch_size - 1)) {
        feature_num = args[ev_id].nnz_ - value_offset;
      } else {
        feature_num = args[ev_id].offset_indices_[bid + 1] - value_offset;
      }
      TValue out = 0.0f;

      const TValue* emb_variable = args[ev_id].emb_variable_;
      const int64_t emb_dim_limit = args[ev_id].emb_row_size_;
      // #pragma unroll
      for (int i = 0; i < feature_num; i++) {
        int indices = int(args[ev_id].sp_values_[value_offset + i]);
        TValue emb_element = emb_variable[indices * emb_vec_size + tid];
        TValue sp_weights =
            args[ev_id].sp_weights_[indices * emb_vec_size + tid];
        // printf("indices is %d emb_element is %f\n", indices, emb_element);
        if (max_norm >= 0.0f) {
          // calc l2 norm of this emb row(per block) and compare with
          // max_norm.
          // if greater than max_norm, then clip every element with factor
          // max_norm / l2norm
          if (tid == 0) {
            l2_sum[0] = 0.0f;
          }
          block.sync();
          atomicAdd(l2_sum, emb_element * emb_element);
          block.sync();
          TValue l2_norm = sqrtf(l2_sum[0]);
          if (l2_norm > max_norm) {
            emb_element *= max_norm / l2_norm;
          }
        }
        out += emb_element * sp_weights;
      }
      out = Combine<combiner>(out, feature_num);
      args[ev_id].emb_vector_[bid * emb_vec_size + tid] = out;
    }
  }
}

template <typename TKey, typename TValue>
class GroupEmbeddingLookupForWard {
 public:
  void initialize(const int num_lookups, const int dimension,
                  const float max_norm) {
    max_norm_ = max_norm;
    dimension_ = dimension;
    ev_nums_ = num_lookups;
    args_size_ = sizeof(GroupEmbeddingForWardArgs<TKey, TValue>);
    CK_CUDA_THROW_(cudaMalloc(&d_args_, args_size_ * num_lookups));
    h_args_.resize(ev_nums_);
  }

  ~GroupEmbeddingLookupForWard() {
    if (d_args_) {
      CK_CUDA_THROW_(cudaFree(d_args_));
    }
  }

  void set(int idx, TValue* emb_variable, TValue* emb_vector,
           int* offset_indices, int nnz, TValue* sp_weights,
           TKey* sp_values = nullptr, int emb_row_size = -1) {
    h_args_[idx].emb_variable_ = emb_variable;
    h_args_[idx].emb_vector_ = emb_vector;
    h_args_[idx].offset_indices_ = offset_indices;
    h_args_[idx].nnz_ = nnz;
    h_args_[idx].sp_weights_ = sp_weights;
    h_args_[idx].sp_values_ = sp_values;
    h_args_[idx].emb_row_size_ = emb_row_size;
  }

  template <typename ForwardFn>
  void Lookup(ForwardFn compute_fn, const int batch_size, const int tile_size,
              cudaStream_t stream) {
    CK_CUDA_THROW_(cudaMemcpyAsync(d_args_, h_args_.data(),
                                   ev_nums_ * args_size_,
                                   cudaMemcpyHostToDevice, stream));

    {
      // TODO: double check why mapped 2D grid slower
      const int block_size = batch_size / 64 * tile_size + 1;
      compute_fn<<<block_size, 64, 0, stream>>>(batch_size, dimension_,
                                                max_norm_, ev_nums_, d_args_);
    }

    CK_CUDA_THROW_(cudaGetLastError());
  }

 protected:
  std::vector<GroupEmbeddingForWardArgs<TKey, TValue>> h_args_;
  GroupEmbeddingForWardArgs<TKey, TValue>* d_args_{nullptr};
  float max_norm_{0.0f};
  int ev_nums_{0};
  int dimension_{0};
  size_t args_size_{0};
};

template <typename TKey, typename TValue>
class GroupEmbeddingLookupForwardBaseOp : public OpKernel {
 public:
  explicit GroupEmbeddingLookupForwardBaseOp(OpKernelConstruction* c)
      : OpKernel(c) {
    OP_REQUIRES_OK(c, c->GetAttr("combiner", &combiner_));
    OP_REQUIRES_OK(c, c->GetAttr("num_lookups", &num_lookups_));
    OP_REQUIRES_OK(c, c->GetAttr("dimension", &dimension_));
    OP_REQUIRES_OK(c, c->GetAttr("max_norm", &max_norm_));
    OP_REQUIRES_OK(c, c->GetAttr("ignore_weights", &ignore_weights_));
    lookuper_.initialize(num_lookups_, dimension_, max_norm_);
  }

  template <bool isEv, Combiner combiner>
  inline void compute(const int batch_size, cudaStream_t stream) {
    if (isEv) {
      if (ignore_weights_) {
        if (dimension_ <= 2) {
          lookuper_.Lookup(EmbeddingVarComputeFn<TKey, TValue, combiner, 2>,
                           batch_size, 2, stream);
        } else if (dimension_ <= 4) {
          lookuper_.Lookup(EmbeddingVarComputeFn<TKey, TValue, combiner, 4>,
                           batch_size, 4, stream);
        } else if (dimension_ <= 8) {
          lookuper_.Lookup(EmbeddingVarComputeFn<TKey, TValue, combiner, 8>,
                           batch_size, 8, stream);
        } else if (dimension_ <= 16) {
          lookuper_.Lookup(EmbeddingVarComputeFn<TKey, TValue, combiner, 16>,
                           batch_size, 16, stream);
        } else if (dimension_ <= 32) {
          lookuper_.Lookup(EmbeddingVarComputeFn<TKey, TValue, combiner, 32>,
                           batch_size, 32, stream);
        } else {
          lookuper_.Lookup(NormalEmbeddingVarComputeFn<TKey, TValue, combiner>,
                           batch_size, 64, stream);
        }
      } else {
        if (dimension_ <= 2) {
          lookuper_.Lookup(
              WeightedEmbeddingVarComputeFn<TKey, TValue, combiner, 2>,
              batch_size, 2, stream);
        } else if (dimension_ <= 4) {
          lookuper_.Lookup(
              WeightedEmbeddingVarComputeFn<TKey, TValue, combiner, 4>,
              batch_size, 4, stream);
        } else if (dimension_ <= 8) {
          lookuper_.Lookup(
              WeightedEmbeddingVarComputeFn<TKey, TValue, combiner, 8>,
              batch_size, 8, stream);
        } else if (dimension_ <= 16) {
          lookuper_.Lookup(
              WeightedEmbeddingVarComputeFn<TKey, TValue, combiner, 16>,
              batch_size, 16, stream);
        } else if (dimension_ <= 32) {
          lookuper_.Lookup(
              WeightedEmbeddingVarComputeFn<TKey, TValue, combiner, 32>,
              batch_size, 32, stream);
        } else {
          lookuper_.Lookup(
              NormalWeightedEmbeddingVarComputeFn<TKey, TValue, combiner>,
              batch_size, 64, stream);
        }
      }
    } else {
      if (ignore_weights_) {
        if (dimension_ <= 2) {
          lookuper_.Lookup(VariableComputeFn<TKey, TValue, combiner, 2>,
                           batch_size, 2, stream);
        } else if (dimension_ <= 4) {
          lookuper_.Lookup(VariableComputeFn<TKey, TValue, combiner, 4>,
                           batch_size, 4, stream);
        } else if (dimension_ <= 8) {
          lookuper_.Lookup(VariableComputeFn<TKey, TValue, combiner, 8>,
                           batch_size, 8, stream);
        } else if (dimension_ <= 16) {
          lookuper_.Lookup(VariableComputeFn<TKey, TValue, combiner, 16>,
                           batch_size, 16, stream);
        } else if (dimension_ <= 32) {
          lookuper_.Lookup(VariableComputeFn<TKey, TValue, combiner, 32>,
                           batch_size, 32, stream);
        } else {
          lookuper_.Lookup(NormalVariableComputeFn<TKey, TValue, combiner>,
                           batch_size, 64, stream);
        }
      } else {
        if (dimension_ <= 2) {
          lookuper_.Lookup(WeightedVariableComputeFn<TKey, TValue, combiner, 2>,
                           batch_size, 2, stream);
        } else if (dimension_ <= 4) {
          lookuper_.Lookup(WeightedVariableComputeFn<TKey, TValue, combiner, 4>,
                           batch_size, 4, stream);
        } else if (dimension_ <= 8) {
          lookuper_.Lookup(WeightedVariableComputeFn<TKey, TValue, combiner, 8>,
                           batch_size, 8, stream);
        } else if (dimension_ <= 16) {
          lookuper_.Lookup(
              WeightedVariableComputeFn<TKey, TValue, combiner, 16>, batch_size,
              16, stream);
        } else if (dimension_ <= 32) {
          lookuper_.Lookup(
              WeightedVariableComputeFn<TKey, TValue, combiner, 32>, batch_size,
              32, stream);
        } else {
          lookuper_.Lookup(
              NormalWeightedVariableComputeFn<TKey, TValue, combiner>,
              batch_size, 64, stream);
        }
      }
    }
  }

 protected:
  GroupEmbeddingLookupForWard<TKey, TValue> lookuper_;
  std::string combiner_;
  float max_norm_;
  int num_lookups_;
  int dimension_;
  bool ignore_weights_;
};

}  // namespace

}  // namespace tensorflow

#endif  // GOOGLE_CUDA