
package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

py_library(
    name = "profiler",
    srcs = ["profiler.py"],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        ":model_analyzer",
        ":option_builder",
        ":tfprof_logger",
        "//tensorflow/core/profiler:protos_all_py",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "option_builder",
    srcs = ["option_builder.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":tfprof_logger",
    ],
)

py_library(
    name = "model_analyzer",
    srcs = ["model_analyzer.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":option_builder",
        ":tfprof_logger",
        "//tensorflow/core/profiler:protos_all_py",
        "//tensorflow/python:errors",
        "//tensorflow/python:pywrap_tensorflow",
        "@six_archive//:six",
    ],
)

py_library(
    name = "tfprof_logger",
    srcs = ["tfprof_logger.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/core/profiler:protos_all_py",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:platform",
        "//tensorflow/python/profiler/internal:flops_registry",
        "@six_archive//:six",
    ],
)

py_library(
    name = "profile_context",
    srcs = ["profile_context.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":model_analyzer",
        ":tfprof_logger",
    ],
)

py_library(
    name = "pprof_profiler",
    srcs = ["pprof_profiler.py"],
    srcs_version = "PY2AND3",
    deps = ["@com_google_pprof//:pprof_proto_py"],
)

py_library(
    name = "traceme",
    srcs = ["traceme.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:platform",
    ],
)

py_library(
    name = "scoped_annotation",
    srcs = ["scoped_annotation.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:platform",
    ],
)
