# Description:
#   Low-level utilities for reading and writing checkpoints.

package(
    default_visibility = [
        "//tensorflow:internal",
    ],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "functional_saver",
    srcs = ["functional_saver.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":saveable_object",
        ":saveable_object_util",
        "//tensorflow/python/eager:def_function",
    ],
)

py_library(
    name = "saveable_object",
    srcs = ["saveable_object.py"],
    srcs_version = "PY2AND3",
)

py_library(
    name = "saveable_object_util",
    srcs = ["saveable_object_util.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:resource_variable_ops",
        "//tensorflow/python:variables",
        "//tensorflow/python/training/tracking:base",
        "@six_archive//:six",
    ],
)
