
package(
    default_visibility = [
        "//engedu/ml/tf_from_scratch:__pkg__",
        "//tensorflow:internal",
    ],
    licenses = ["notice"],  # Apache 2.0
)

py_library(
    name = "losses",
    srcs = [
        "__init__.py",
        "losses.py",
        "losses_impl.py",
        "util.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:array_ops",
        "//tensorflow/python:confusion_matrix",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:nn",
        "//tensorflow/python:nn_ops",
        "//tensorflow/python:platform",
        "//tensorflow/python:util",
        "//tensorflow/python:weights_broadcast_ops",
    ],
)

py_library(
    name = "loss_reduction",
    srcs = ["loss_reduction.py"],
    srcs_version = "PY2AND3",
)

