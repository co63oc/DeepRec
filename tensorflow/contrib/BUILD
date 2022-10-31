# Description:
#   contains parts of TensorFlow that are experimental or unstable and which are not supported.

load("//third_party/mpi:mpi.bzl", "if_mpi")
load("//tensorflow:tensorflow.bzl", "if_not_windows")

package(
    default_visibility = ["//tensorflow:__subpackages__"],
    licenses = ["notice"],  # Apache 2.0
)

py_library(
    name = "contrib_py",
    srcs = glob(
        ["**/*.py"],
        exclude = [
            "**/*_test.py",
        ],
    ),
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow/contrib/compiler:compiler_py",
        "//tensorflow/contrib/compiler:xla",
        "//tensorflow/contrib/autograph",
        "//tensorflow/contrib/crf:crf_py",
        "//tensorflow/contrib/data",
        "//tensorflow/contrib/rnn:rnn_py",
        "//tensorflow/contrib/rpc",
        "//tensorflow/contrib/training:training_py",
        "//tensorflow/contrib/util:util_py",
        "//tensorflow/python:util",
        "//tensorflow/python/estimator:estimator_py",
    ] + if_mpi(["//tensorflow/contrib/mpi_collectives:mpi_collectives_py"]) + select({
        "//tensorflow:android": [],
        "//tensorflow:ios": [],
        "//tensorflow:linux_s390x": [],
        "//tensorflow:windows": [],
        "//tensorflow:no_kafka_support": [],
        "//conditions:default": [
        ],
    }) + select({
        "//tensorflow:android": [],
        "//tensorflow:ios": [],
        "//tensorflow:linux_s390x": [],
        "//tensorflow:windows": [],
        "//conditions:default": [
            "//tensorflow/contrib/fused_conv:fused_conv_py",
            "//tensorflow/contrib/tensorrt:init_py",
        ],
    }),
)

cc_library(
    name = "contrib_kernels",
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow/contrib/rnn:all_kernels",
    ] + if_mpi(["//tensorflow/contrib/mpi_collectives:mpi_collectives_py"]) + select({
        "//tensorflow:android": [],
        "//tensorflow:ios": [],
        "//tensorflow:linux_s390x": [],
        "//tensorflow:windows": [],
        "//tensorflow:no_kafka_support": [],
        "//conditions:default": [
            #"//tensorflow/contrib/kafka:dataset_kernels",
        ],
    }) + if_not_windows([
        "//tensorflow/contrib/tensorrt:trt_op_kernels",
    ]),
)

cc_library(
    name = "contrib_ops_op_lib",
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow/contrib/rnn:all_ops",
    ] + if_not_windows([
        "//tensorflow/compiler/tf2tensorrt:trt_op_libs",
    ]),
)
