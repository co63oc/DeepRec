
package(
    default_visibility = ["//tensorflow:internal"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "benchmark_base",
    srcs = ["benchmark_base.py"],
    deps = [
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:session",
        "//tensorflow/python/data/ops:dataset_ops",
        "//third_party/py/numpy",
    ],
)


