
package(
    default_visibility = ["//tensorflow:internal"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "module",
    srcs = ["module.py"],
    deps = [
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:tf2",
        "//tensorflow/python:util",
        "//tensorflow/python:variables",
        "//tensorflow/python/training/tracking",
        "@six_archive//:six",
    ],
)

