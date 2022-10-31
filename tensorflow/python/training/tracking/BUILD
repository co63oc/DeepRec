# Description:
#   Utilities for reading and writing object-based checkpoints.

load(
    "//tensorflow/tools/test:performance.bzl",
    "tf_py_logged_benchmark",
)

package(
    default_visibility = [
        "//tensorflow:internal",
    ],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "base",
    srcs = ["base.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:array_ops",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:io_ops_gen",
        "//tensorflow/python:platform",
        "//tensorflow/python:util",
        "//tensorflow/python/eager:context",
        "//tensorflow/python/training/saving:saveable_object",
        "@six_archive//:six",
    ],
)

py_library(
    name = "tracking",
    srcs = ["tracking.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base",
        ":data_structures",
    ],
)

py_library(
    name = "layer_utils",
    srcs = ["layer_utils.py"],
    srcs_version = "PY2AND3",
)

py_library(
    name = "data_structures",
    srcs = ["data_structures.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base",
        ":layer_utils",
        "//tensorflow/python/saved_model:revived_types",
        "@wrapt",
    ],
)

py_library(
    name = "graph_view",
    srcs = ["graph_view.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base",
        ":tracking",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python/training/saving:saveable_object",
        "//tensorflow/python/training/saving:saveable_object_util",
    ],
)

py_library(
    name = "util",
    srcs = ["util.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base",
        ":data_structures",
        ":graph_view",
        ":tracking",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:checkpoint_management",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:errors",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:init_ops",
        "//tensorflow/python:io_ops_gen",
        "//tensorflow/python:lib",
        "//tensorflow/python:platform",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python:saver",
        "//tensorflow/python:session",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:tensor_util",
        "//tensorflow/python:util",
        "//tensorflow/python:variable_scope",
        "//tensorflow/python:variables",
        "//tensorflow/python/eager:context",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/keras:backend",
        "//tensorflow/python/training/saving:functional_saver",
        "//tensorflow/python/training/saving:saveable_object_util",
        "@six_archive//:six",
    ],
)

py_library(
    name = "python_state",
    srcs = ["python_state.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base",
    ],
)

tf_py_logged_benchmark(
    name = "benchmarks",
    target = "//tensorflow/python/training/tracking:benchmarks_test",
)
