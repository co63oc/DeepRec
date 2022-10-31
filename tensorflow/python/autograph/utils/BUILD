
package(
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

filegroup(
    name = "all_files",
    srcs = glob(
        ["**/*"],
        exclude = [
            "**/METADATA",
            "**/OWNERS",
        ],
    ),
    visibility = ["//tensorflow:__subpackages__"],
)

py_library(
    name = "utils",
    srcs = [
        "__init__.py",
        "ag_logging.py",
        "context_managers.py",
        "misc.py",
        "py_func.py",
        "tensor_list.py",
        "tensors.py",
        "testing.py",
        "type_check.py",
    ],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:__subpackages__"],
    deps = [
        "//tensorflow/python:dtypes",
        "//tensorflow/python:list_ops",
        "//tensorflow/python:platform",
        "//tensorflow/python:script_ops",
        "//tensorflow/python:util",
        "//tensorflow/python/autograph/pyct",
        "//tensorflow/python/data/ops:dataset_ops",
        "@six_archive//:six",
    ],
)


