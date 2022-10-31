load(
    "//tensorflow/tools/test:performance.bzl",
    "tf_py_logged_benchmark",
)

package(
    licenses = ["notice"],  # Apache 2.0
)

cc_library(
    name = "pywrap_tfe_lib",
    srcs = [
        "pywrap_tensor.cc",
        "pywrap_tensor_conversion.cc",
        "pywrap_tfe_src.cc",
    ],
    hdrs = [
        "pywrap_tensor.h",
        "pywrap_tensor_conversion.h",
        "pywrap_tfe.h",
    ],
    visibility = [
        "//learning/deepmind/courier:__subpackages__",
        "//tensorflow:internal",
    ],
    deps = [
        "//tensorflow/c:c_api",
        "//tensorflow/c:c_api_internal",
        "//tensorflow/c/eager:c_api",
        "//tensorflow/c/eager:c_api_experimental",
        "//tensorflow/c/eager:c_api_internal",
        "//tensorflow/c/eager:tape",
        "//tensorflow/core:framework",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core/common_runtime/eager:tensor_handle",
        "//tensorflow/core/platform:logging",
        "//tensorflow/core/platform:types",
        "//tensorflow/python:cpp_python_util",
        "//tensorflow/python:ndarray_tensor",
        "//tensorflow/python:ndarray_tensor_bridge",
        "//tensorflow/python:numpy_lib",
        "//tensorflow/python:py_seq_tensor",
        "//tensorflow/python:safe_ptr",
        "//third_party/py/numpy:headers",
        "//third_party/python_runtime:headers",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/types:variant",
    ],
)

# Transitive dependencies of this target will be included in the pip package.
py_library(
    name = "eager_pip",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":backprop",
        ":cancellation",
        ":context",
        ":core",
        ":def_function",
        ":execute",
        ":execution_callbacks",
        ":forwardprop",
        ":function",
        ":graph_only_ops",
        ":monitoring",
        ":profiler",
        ":profiler_client",
        ":tape",
        ":test",
        ":wrap_function",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python/eager/memory_tests:memory_test_util",
    ],
)

py_library(
    name = "core",
    srcs = ["core.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":context",
        "//tensorflow/python:errors",
        "//tensorflow/python:pywrap_tensorflow",
    ],
)

py_library(
    name = "cancellation",
    srcs = ["cancellation.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        "//tensorflow/python:pywrap_tensorflow",
    ],
)

py_library(
    name = "executor",
    srcs = ["executor.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        "//tensorflow/python:pywrap_tensorflow",
    ],
)

py_library(
    name = "context",
    srcs = ["context.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":executor",
        ":monitoring",
        "//tensorflow/python:device",
        "//tensorflow/python:device_spec",
        "//tensorflow/python:errors",
        "//tensorflow/python:platform",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python:tf2",
        "//tensorflow/python:util",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "monitoring",
    srcs = ["monitoring.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        "//tensorflow/python:c_api_util",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "profiler",
    srcs = ["profiler.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":context",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "profiler_client",
    srcs = ["profiler_client.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        "//tensorflow/python:pywrap_tensorflow",
    ],
)

py_library(
    name = "tape",
    srcs = ["tape.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
)

py_library(
    name = "test",
    srcs = ["test.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":core",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:framework_ops",
    ],
)

py_library(
    name = "execute",
    srcs = ["execute.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":context",
        ":core",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:lib",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:util",
        "@six_archive//:six",
    ],
)

py_library(
    name = "execution_callbacks",
    srcs = ["execution_callbacks.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":context",
        "//tensorflow/python:op_callbacks",
        "//tensorflow/python:pywrap_tensorflow",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "graph_only_ops",
    srcs = ["graph_only_ops.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:tensor_shape",
    ],
)

py_library(
    name = "framework_for_generated_wrappers",
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        ":execute",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:tensor_shape",
    ],
)

py_library(
    name = "function",
    srcs = ["function.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":context",
        ":core",
        ":execute",
        ":graph_only_ops",
        ":tape",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:errors",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:func_graph",
        "//tensorflow/python:gradients_impl",
        "//tensorflow/python:graph_to_function_def",
        "//tensorflow/python:util",
        "//third_party/py/numpy",
        "@six_archive//:six",
    ],
)

py_library(
    name = "backprop",
    srcs = ["backprop.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":context",
        ":execute",
        ":imperative_grad",
        ":tape",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:errors",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:unconnected_gradients",
        "//tensorflow/python:util",
        "//tensorflow/python/ops/parallel_for:control_flow_ops",
        "@six_archive//:six",
    ],
)

py_library(
    name = "forwardprop",
    srcs = ["forwardprop.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        "//tensorflow/python:platform",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python:util",
    ],
)

tf_py_logged_benchmark(
    name = "benchmarks",
    target = "//tensorflow/python/eager:benchmarks_test",
)

py_library(
    name = "imperative_grad",
    srcs = ["imperative_grad.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python:unconnected_gradients",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "def_function",
    srcs = ["def_function.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":context",
        ":function",
        ":lift_to_graph",
        "//tensorflow/python:cond_v2",  # TODO(b/118513001): Imported via control_flow_ops; remove.
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:resource_variable_ops",
        "//tensorflow/python:util",
        "//tensorflow/python:variable_scope",
        "//tensorflow/python:while_v2",  # TODO(b/118513001): Imported via control_flow_ops; remove.
        "//tensorflow/python/training/tracking:base",
    ],
)

py_library(
    name = "lift_to_graph",
    srcs = ["lift_to_graph.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:op_selector",
        "@six_archive//:six",
    ],
)

py_library(
    name = "wrap_function",
    srcs = ["wrap_function.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":context",
        ":function",
        ":lift_to_graph",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:template",
        "//tensorflow/python:variable_scope",
        "//tensorflow/python/saved_model:nested_structure_coder",
        "//tensorflow/python/training/tracking:base",
    ],
)

py_library(
    name = "remote",
    srcs = ["remote.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":context",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:platform",
    ],
)

