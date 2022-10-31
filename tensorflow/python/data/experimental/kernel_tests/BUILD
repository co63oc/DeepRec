
package(
    default_visibility = ["//tensorflow:internal"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "reader_dataset_ops_test_base",
    srcs = [
        "reader_dataset_ops_test_base.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:lib",
        "//tensorflow/python:parsing_ops",
        "//tensorflow/python:util",
        "//tensorflow/python/data/experimental/ops:readers",
        "//tensorflow/python/data/kernel_tests:test_base",
        "//tensorflow/python/data/ops:iterator_ops",
        "//tensorflow/python/data/ops:readers",
    ],
)

py_library(
    name = "sql_dataset_test_base",
    srcs = ["sql_dataset_test_base.py"],
    srcs_version = "PY2AND3",
    visibility = [
        "//tensorflow/python/data/experimental/kernel_tests:__pkg__",
        "//tensorflow/python/data/experimental/kernel_tests/serialization:__pkg__",
    ],
    deps = [
        "//tensorflow/python:array_ops",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:dtypes",
        "//tensorflow/python/data/experimental/ops:readers",
        "//tensorflow/python/data/kernel_tests:test_base",
        "@org_sqlite//:python",
    ],
)

py_library(
    name = "stats_dataset_test_base",
    srcs = ["stats_dataset_test_base.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python/data/kernel_tests:test_base",
    ],
)

