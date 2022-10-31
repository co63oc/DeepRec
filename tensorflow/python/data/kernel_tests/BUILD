# Tests of TensorFlow kernels written using the Python API.

load("//tensorflow:tensorflow.bzl", "tf_py_test")

package(
    default_visibility = ["//tensorflow:internal"],
    licenses = ["notice"],  # Apache 2.0
)

py_library(
    name = "test_base",
    srcs = ["test_base.py"],
    deps = [
        "//tensorflow/python:array_ops",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:errors",
        "//tensorflow/python:framework_combinations",
        "//tensorflow/python:framework_test_lib",
        "//tensorflow/python:sparse_tensor",
        "//tensorflow/python/data/ops:dataset_ops",
        "//tensorflow/python/data/util:nest",
        "//tensorflow/python/eager:context",
        "//tensorflow/python/ops/ragged",
    ],
)


