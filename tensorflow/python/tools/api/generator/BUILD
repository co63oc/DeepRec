# Description:
# Scripts used to generate TensorFlow Python API.

load("//tensorflow/python/tools/api/generator:api_init_files.bzl", "TENSORFLOW_API_INIT_FILES")
load("//tensorflow/python/tools/api/generator:api_init_files_v1.bzl", "TENSORFLOW_API_INIT_FILES_V1")
load("//tensorflow/python/tools/api/generator:api_init_files.bzl", "KERAS_API_INIT_FILES")
load("//tensorflow/python/tools/api/generator:api_init_files_v1.bzl", "KERAS_API_INIT_FILES_V1")

package(
    licenses = ["notice"],  # Apache 2.0
)

exports_files(
    [
        "LICENSE",
        "create_python_api.py",
    ],
)

py_library(
    name = "create_python_api",
    srcs = ["//tensorflow/python/tools/api/generator:create_python_api.py"],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow/python:util",
        "//tensorflow/python/tools/api/generator:doc_srcs",
    ],
)

py_library(
    name = "doc_srcs",
    srcs = ["doc_srcs.py"],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow/python:util",
    ],
)


