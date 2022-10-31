
package(
    default_visibility = ["//tensorflow:internal"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "nest",
    srcs = ["nest.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:util",
        "@six_archive//:six",
    ],
)

py_library(
    name = "sparse",
    srcs = ["sparse.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":nest",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:ops",
        "//tensorflow/python:sparse_ops",
        "//tensorflow/python:sparse_tensor",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:util",
        "@six_archive//:six",
    ],
)

py_library(
    name = "structure",
    srcs = ["structure.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":nest",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:ops",
        "//tensorflow/python:sparse_ops",
        "//tensorflow/python:sparse_tensor",
        "//tensorflow/python:tensor_array_ops",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:tensor_util",
        "//tensorflow/python:util",
        "//tensorflow/python/ops/ragged",
    ],
)

py_library(
    name = "options",
    srcs = ["options.py"],
    srcs_version = "PY2AND3",
)

py_library(
    name = "convert",
    srcs = ["convert.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:constant_op",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:tensor_shape",
    ],
)

py_library(
    name = "random_seed",
    srcs = ["random_seed.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:constant_op",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework",
    ],
)

py_library(
    name = "traverse",
    srcs = ["traverse.py"],
    srcs_version = "PY2AND3",
    deps = [
    ],
)


