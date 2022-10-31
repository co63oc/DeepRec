# Description:
#   keras/distribute package is intended to serve as the centralized place for things
#   related to dist-strat used by Keras..

package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "distribute",
    srcs = [
        "__init__.py",
        "distributed_training_utils.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:client_testlib",
        "//tensorflow/python/data",
        "//tensorflow/python/distribute:distribute_coordinator",
        "//tensorflow/python/distribute:distribute_lib",
        "//tensorflow/python/distribute:input_lib",
        "//tensorflow/python/distribute:one_device_strategy",
        "//tensorflow/python/distribute:reduce_util",
        "//tensorflow/python/distribute:values",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/keras:activations",
        "//tensorflow/python/keras:backend",
        "//tensorflow/python/keras:callbacks",
        "//tensorflow/python/keras:callbacks_v1",
        "//tensorflow/python/keras:constraints",
        "//tensorflow/python/keras:engine_utils",
        "//tensorflow/python/keras:initializers",
        "//tensorflow/python/keras:losses",
        "//tensorflow/python/keras:mode_keys",
        "//tensorflow/python/keras:optimizers",
        "//tensorflow/python/keras:regularizers",
        "//tensorflow/python/keras:saving",
        "//tensorflow/python/keras/distribute:multi_worker_training_state",
        "//tensorflow/python/keras/mixed_precision/experimental:autocast_variable",
        "//tensorflow/python/keras/mixed_precision/experimental:policy",
        "//tensorflow/python/training/tracking:data_structures",
        "//tensorflow/tools/docs:doc_controls",
    ],
)

py_library(
    name = "multi_worker_training_state",
    srcs = [
        "multi_worker_training_state.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python/distribute:multi_worker_util",
    ],
)

py_library(
    name = "distribute_strategy_test_lib",
    srcs = [
        "distribute_strategy_test.py",
    ],
    deps = [
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:training",
        "//tensorflow/python/distribute:combinations",
        "//tensorflow/python/distribute:distribute_lib",
        "//tensorflow/python/distribute:mirrored_strategy",
        "//tensorflow/python/distribute:strategy_combinations",
        "//tensorflow/python/eager:context",
        "//tensorflow/python/eager:test",
        "//tensorflow/python/estimator:estimator_py",
        "//tensorflow/python/keras",
        "//third_party/py/numpy",
        "@absl_py//absl/testing:parameterized",
    ],
)

py_library(
    name = "keras_correctness_test_lib",
    srcs = [
        "keras_correctness_test_base.py",
        "keras_dnn_correctness_test.py",
        "keras_embedding_model_correctness_test.py",
        "keras_image_model_correctness_test.py",
        "keras_lstm_model_correctness_test.py",
        "keras_stateful_lstm_model_correctness_test.py",
    ],
    deps = [
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:training",
        "//tensorflow/python/distribute:combinations",
        "//tensorflow/python/distribute:distribute_lib",
        "//tensorflow/python/distribute:mirrored_strategy",
        "//tensorflow/python/distribute:strategy_combinations",
        "//tensorflow/python/eager:context",
        "//tensorflow/python/eager:test",
        "//tensorflow/python/keras",
        "//tensorflow/python/keras:backend",
        "//third_party/py/numpy",
        "@absl_py//absl/testing:parameterized",
    ],
)

py_library(
    name = "keras_test_lib",
    srcs = [
        "keras_utils_test.py",
    ],
    deps = [
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:training",
        "//tensorflow/python/distribute:combinations",
        "//tensorflow/python/distribute:mirrored_strategy",
        "//tensorflow/python/distribute:parameter_server_strategy",
        "//tensorflow/python/distribute:strategy_combinations",
        "//tensorflow/python/eager:test",
        "//tensorflow/python/keras",
        "//third_party/py/numpy",
        "@absl_py//absl/testing:parameterized",
    ],
)

py_library(
    name = "multi_worker_testing_utils",
    srcs = [
        "multi_worker_testing_utils.py",
    ],
    deps = [
        "//tensorflow/python:array_ops",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:random_ops",
        "//tensorflow/python/data/ops:dataset_ops",
        "//tensorflow/python/keras",
        "//tensorflow/python/keras/optimizer_v2",
    ],
)
