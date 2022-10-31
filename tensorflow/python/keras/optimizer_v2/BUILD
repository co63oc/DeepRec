# Description:
#   Contains the Keras OptimizerV2 API (internal TensorFlow version).

package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "optimizer_v2",
    srcs = [
        "adadelta.py",
        "adagrad.py",
        "adam.py",
        "adamax.py",
        "ftrl.py",
        "gradient_descent.py",
        "nadam.py",
        "optimizer_v2.py",
        "rmsprop.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":learning_rate_schedule",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:framework",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:resource_variable_ops",
        "//tensorflow/python:state_ops",
        "//tensorflow/python:variable_scope",
        "//tensorflow/python:variables",
        "//tensorflow/python/distribute:distribute_lib",
        "//tensorflow/python/distribute:reduce_util",
        "//tensorflow/python/distribute:values",
        "//tensorflow/python/keras:backend",
        "//tensorflow/python/keras:backend_config",
        "//tensorflow/python/keras:base_layer_utils",
        "//tensorflow/python/keras:initializers",
        "//tensorflow/python/keras:tf_utils",
    ],
)

py_library(
    name = "learning_rate_schedule",
    srcs = [
        "learning_rate_schedule.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:framework",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:random_ops",
        "//tensorflow/python/keras:generic_utils",
    ],
)

