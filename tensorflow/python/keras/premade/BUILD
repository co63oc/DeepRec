# Description:
#   Contains the Keras Premade Models (internal TensorFlow version).

package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "premade",
    srcs = [
        "__init__.py",
        "linear.py",
        "wide_deep.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:framework",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:variable_scope",
        "//tensorflow/python:variables",
        "//tensorflow/python/keras:backend_config",
        "//tensorflow/python/keras:regularizers",
    ],
)

