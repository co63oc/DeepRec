# Description:
#   Contains the Keras API (internal TensorFlow version).

load("//tensorflow:tensorflow.bzl", "tf_py_test")

package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

config_setting(
    name = "empty_condition",
    values = {"define": "UNUSED=unused"},
)

py_library(
    name = "keras",
    srcs = [
        "__init__.py",
        "applications/__init__.py",
        "applications/densenet.py",
        "applications/imagenet_utils.py",
        "applications/inception_resnet_v2.py",
        "applications/inception_v3.py",
        "applications/mobilenet.py",
        "applications/mobilenet_v2.py",
        "applications/nasnet.py",
        "applications/resnet.py",
        "applications/resnet_v2.py",
        "applications/vgg16.py",
        "applications/vgg19.py",
        "applications/xception.py",
        "datasets/__init__.py",
        "datasets/boston_housing.py",
        "datasets/cifar.py",
        "datasets/cifar10.py",
        "datasets/cifar100.py",
        "datasets/fashion_mnist.py",
        "datasets/imdb.py",
        "datasets/mnist.py",
        "datasets/reuters.py",
        "estimator/__init__.py",
        "keras_parameterized.py",
        "ops.py",
        "preprocessing/__init__.py",
        "preprocessing/image.py",
        "preprocessing/sequence.py",
        "preprocessing/text.py",
        "testing_utils.py",
        "utils/__init__.py",
        "utils/multi_gpu_utils.py",
        "utils/np_utils.py",
        "utils/vis_utils.py",
        "wrappers/__init__.py",
        "wrappers/scikit_learn.py",
    ],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        ":backend",
        ":engine",
        ":layers",
        ":pil_for_keras",
        ":saving",
        "//tensorflow/python:training",
        "//tensorflow/python/keras/mixed_precision/experimental:mixed_precision_experimental",
        "//tensorflow/python/keras/optimizer_v2",
        "//tensorflow/python/keras/premade",
        "//tensorflow/python/saved_model",
        "@keras_applications_archive//:keras_applications",
    ],
)

py_library(
    name = "pil_for_keras",
    deps = select({
        ":empty_condition": [],
        "//conditions:default": [],
    }),
)

py_library(
    name = "backend",
    srcs = ["backend.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":backend_config",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:check_ops",
        "//tensorflow/python:client",
        "//tensorflow/python:clip_ops",
        "//tensorflow/python:composite_tensor_utils",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:ctc_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:functional_ops",
        "//tensorflow/python:gradients",
        "//tensorflow/python:image_ops",
        "//tensorflow/python:init_ops",
        "//tensorflow/python:init_ops_v2",
        "//tensorflow/python:logging_ops",
        "//tensorflow/python:map_fn",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:metrics",
        "//tensorflow/python:nn",
        "//tensorflow/python:platform",
        "//tensorflow/python:random_ops",
        "//tensorflow/python:session",
        "//tensorflow/python:sparse_ops",
        "//tensorflow/python:sparse_tensor",
        "//tensorflow/python:state_ops",
        "//tensorflow/python:summary",
        "//tensorflow/python:tensor_array_grad",
        "//tensorflow/python:tensor_array_ops",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:training_lib",
        "//tensorflow/python:util",
        "//tensorflow/python:variables",
        "//tensorflow/python/distribute:distribute_coordinator",
        "//tensorflow/python/distribute:distribute_lib",
        "//tensorflow/python/distribute:multi_worker_util",
    ],
)

py_library(
    name = "backend_config",
    srcs = ["backend_config.py"],
    srcs_version = "PY2AND3",
)

py_library(
    name = "base_layer_utils",
    srcs = ["engine/base_layer_utils.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":tf_utils",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:auto_control_deps",
        "//tensorflow/python:control_flow_v2_func_graphs",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:init_ops",
        "//tensorflow/python:init_ops_v2",
        "//tensorflow/python:tf2",
        "//tensorflow/python:util",
        "//tensorflow/python:variables",
        "//tensorflow/python/distribute:distribute_lib",
        "//tensorflow/python/eager:context",
    ],
)

py_library(
    name = "engine",
    srcs = [
        "engine/__init__.py",
        "engine/input_layer.py",
        "engine/network.py",
        "engine/node.py",
        "engine/partial_batch_padding_handler.py",
        "engine/saving.py",
        "engine/sequential.py",
        "engine/training.py",
        "engine/training_arrays.py",
        "engine/training_distributed.py",
        "engine/training_eager.py",
        "engine/training_generator.py",
        "engine/training_utils.py",
        "engine/training_v2.py",
        "engine/training_v2_utils.py",
        "metrics.py",  # Need base_layer
        "models.py",
        "utils/metrics_utils.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":activations",
        ":backend",
        ":base_layer",
        ":base_preprocessing_layer",
        ":callbacks",
        ":callbacks_v1",
        ":constraints",
        ":data_adapter",
        ":engine_utils",
        ":initializers",
        ":input_spec",
        ":losses",
        ":mode_keys",
        ":optimizers",
        ":regularizers",
        ":saving",
        "//tensorflow/python:composite_tensor_utils",
        "//tensorflow/python/data",
        "//tensorflow/python/distribute:distribute_coordinator",
        "//tensorflow/python/distribute:distribute_lib",
        "//tensorflow/python/distribute:input_lib",
        "//tensorflow/python/distribute:reduce_util",
        "//tensorflow/python/eager:monitoring",
        "//tensorflow/python/keras/distribute",
        "//tensorflow/python/keras/mixed_precision/experimental:autocast_variable",
        "//tensorflow/python/keras/mixed_precision/experimental:loss_scale_optimizer",
        "//tensorflow/python/keras/mixed_precision/experimental:policy",
        "//tensorflow/python/module",
        "//tensorflow/python/ops/ragged:ragged_tensor",
        "//tensorflow/python/ops/ragged:ragged_util",
        "//tensorflow/python/training/tracking:data_structures",
        "//tensorflow/tools/docs:doc_controls",
        "@six_archive//:six",
    ],
)

py_library(
    name = "data_adapter",
    srcs = ["engine/data_adapter.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":engine_utils",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:util",
        "//tensorflow/python/data/ops:dataset_ops",
    ],
)

py_library(
    name = "input_spec",
    srcs = ["engine/input_spec.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:lib",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:tensor_spec",
        "@six_archive//:six",
    ],
)

py_library(
    name = "base_layer",
    srcs = ["engine/base_layer.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":base_layer_utils",
        ":constraints",
        ":engine_utils",
        ":regularizers",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:constant_op",
        "//tensorflow/python/data",
        "//tensorflow/python/distribute:distribute_coordinator",
        "//tensorflow/python/distribute:distribute_lib",
        "//tensorflow/python/distribute:input_lib",
        "//tensorflow/python/distribute:reduce_util",
        "//tensorflow/python/eager:monitoring",
        "//tensorflow/python/keras/distribute",
        "//tensorflow/python/keras/mixed_precision/experimental:autocast_variable",
        "//tensorflow/python/keras/mixed_precision/experimental:loss_scale_optimizer",
        "//tensorflow/python/keras/mixed_precision/experimental:policy",
        "//tensorflow/python/module",
        "//tensorflow/python/training/tracking:data_structures",
        "//tensorflow/tools/docs:doc_controls",
        "@six_archive//:six",
    ],
)

py_library(
    name = "base_preprocessing_layer",
    srcs = [
        "engine/base_preprocessing_layer.py",
        "engine/base_preprocessing_layer_v1.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":base_layer",
        "//tensorflow/python:composite_tensor_utils",
        "//tensorflow/python/data",
        "//tensorflow/python/eager:monitoring",
        "//tensorflow/python/module",
    ],
)

py_library(
    name = "saving",
    srcs = [
        "saving/__init__.py",
        "saving/hdf5_format.py",
        "saving/model_config.py",
        "saving/save.py",
        "saving/saved_model/constants.py",
        "saving/saved_model/load.py",
        "saving/saved_model/save.py",
        "saving/saved_model/serialized_attributes.py",
        "saving/saved_model/utils.py",
        "saving/saved_model_experimental.py",
        "saving/saving_utils.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":engine_utils",
        ":input_spec",
        ":mode_keys",
        ":optimizers",
        ":regularizers",
        "//tensorflow/python:lib",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:saver",
        "//tensorflow/python:tensor_spec",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/saved_model",
        "//tensorflow/python/saved_model/model_utils",
        "//tensorflow/python/training/tracking",
    ],
)

py_library(
    name = "activations",
    srcs = [
        "activations.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":engine_utils",
    ],
)

py_library(
    name = "callbacks",
    srcs = [
        "callbacks.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":engine_utils",
        ":mode_keys",
        "//tensorflow/python/keras/distribute:multi_worker_training_state",
    ],
)

py_library(
    name = "callbacks_v1",
    srcs = [
        "callbacks_v1.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":engine_utils",
        "//tensorflow/python/eager:profiler",
    ],
)

py_library(
    name = "constraints",
    srcs = [
        "constraints.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":engine_utils",
    ],
)

py_library(
    name = "initializers",
    srcs = [
        "initializers.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":engine_utils",
        "//tensorflow/python:init_ops_v2",
    ],
)

py_library(
    name = "losses",
    srcs = [
        "losses.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":engine_utils",
    ],
)

py_library(
    name = "optimizers",
    srcs = [
        "optimizers.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":engine_utils",
        "//tensorflow/python/keras/optimizer_v2",
    ],
)

py_library(
    name = "regularizers",
    srcs = [
        "regularizers.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        ":engine_utils",
    ],
)

py_library(
    name = "engine_utils",
    srcs = [
        "utils/conv_utils.py",
        "utils/data_utils.py",
        "utils/io_utils.py",
        "utils/losses_utils.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":backend",
        "//tensorflow/python/ops/losses:loss_reduction",
    ],
)

py_library(
    name = "tf_utils",
    srcs = ["utils/tf_utils.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:composite_tensor",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:smart_cond",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:tensor_util",
        "//tensorflow/python:util",
        "//tensorflow/python:variables",
        "//tensorflow/python/eager:context",
        "@six_archive//:six",
    ],
)

# A separate build for layers without serialization to avoid circular deps
# with feature column.
py_library(
    name = "layers_base",
    srcs = [
        "layers/__init__.py",
        "layers/advanced_activations.py",
        "layers/convolutional.py",
        "layers/convolutional_recurrent.py",
        "layers/core.py",
        "layers/cudnn_recurrent.py",
        "layers/dense_attention.py",
        "layers/embeddings.py",
        "layers/kernelized.py",
        "layers/local.py",
        "layers/merge.py",
        "layers/noise.py",
        "layers/normalization.py",
        "layers/normalization_v2.py",
        "layers/pooling.py",
        "layers/preprocessing/normalization.py",
        "layers/preprocessing/normalization_v1.py",
        "layers/recurrent.py",
        "layers/recurrent_v2.py",
        "layers/rnn_cell_wrapper_v2.py",
        "layers/wrappers.py",
        "utils/kernelized_utils.py",
        "utils/layer_utils.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":engine",
        ":generic_utils",
        ":tf_utils",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:control_flow_util",
        "//tensorflow/python:cudnn_rnn_ops_gen",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:embedding_ops",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:init_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:nn",
        "//tensorflow/python:nn_ops",
        "//tensorflow/python:platform",
        "//tensorflow/python:sparse_tensor",
        "//tensorflow/python:standard_ops",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:tensor_util",
        "//tensorflow/python:util",
        "//tensorflow/python:variables",
        "//tensorflow/python/distribute:distribute_lib",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "preprocessing_test_utils",
    srcs = ["layers/preprocessing/preprocessing_test_utils.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":keras",
        "//tensorflow/python:client_testlib",
        "@absl_py//absl/testing:parameterized",
    ],
)

py_library(
    name = "layers",
    srcs = [
        "layers/serialization.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":layers_base",
        ":tf_utils",
        "//tensorflow/python/feature_column:feature_column_py",
    ],
)

py_library(
    name = "generic_utils",
    srcs = [
        "utils/generic_utils.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:util",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "mode_keys",
    srcs = [
        "utils/mode_keys.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python/saved_model/model_utils:mode_keys",
    ],
)

py_library(
    name = "model_subclassing_test_util",
    srcs = ["model_subclassing_test_util.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":keras",
    ],
)

