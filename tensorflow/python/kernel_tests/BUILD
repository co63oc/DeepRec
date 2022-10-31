# Tests of TensorFlow kernels written using the Python API.

load("//tensorflow:tensorflow.bzl", "sycl_py_test", "tf_custom_op_library")

package(
    default_visibility = ["//tensorflow:internal"],
    licenses = ["notice"],  # Apache 2.0
)

# CPU only tests should use tf_py_test, GPU tests use cuda_py_test
# Please avoid the py_tests and cuda_py_tests (plural) while we
# fix the shared/overbroad dependencies.

py_library(
    name = "cudnn_deterministic_base",
    srcs = ["cudnn_deterministic_base.py"],
    deps = [
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:nn_ops",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "bias_op_base",
    srcs = ["bias_op_base.py"],
    deps = [
        "//tensorflow/python:array_ops",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:gradients",
        "//tensorflow/python:nn_grad",
        "//tensorflow/python:nn_ops",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "sparse_tensor_dense_matmul_op_base",
    srcs = ["sparse_tensor_dense_matmul_op_base.py"],
    deps = [
        "//third_party/py/numpy",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:client",
        "//tensorflow/python:framework",
        "//tensorflow/python:platform",
        "//tensorflow/python:sparse_ops",
    ],
)

sycl_py_test(
    name = "basic_gpu_test",
    size = "small",
    srcs = ["basic_gpu_test.py"],
    additional_deps = [
        "//third_party/py/numpy",
        "//tensorflow/python:array_ops_gen",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:math_ops_gen",
    ],
)

# Custom op tests
tf_custom_op_library(
    name = "ackermann_op.so",
    srcs = ["ackermann_op.cc"],
)

tf_custom_op_library(
    name = "duplicate_op.so",
    srcs = ["duplicate_op.cc"],
)

tf_custom_op_library(
    name = "invalid_op.so",
    srcs = ["invalid_op.cc"],
)

