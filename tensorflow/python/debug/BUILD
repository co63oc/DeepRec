# Description:
#   Python Client Code of the TensorFlow Debugger (tfdbg).
#
# Public target(s):
#
# ":debug_py": Public Python methods and classes of tfdbg.
#   For API documentation, see https://www.tensorflow.org/api_docs/python/tfdbg
#   For a user interface walkthrough, see https://www.tensorflow.org/guide/debugger
# ":grpc_debug_server": Server interface for grpc:// debug URLs.

load("//tensorflow:tensorflow.bzl", "if_not_v2", "if_not_windows", "py_binary")

package(
    default_visibility = ["//tensorflow:internal"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "debug_py",
    srcs = ["__init__.py"],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        ":debug_data",
        ":debug_gradients",
        ":debug_graphs",
        ":debug_utils",
        ":grpc_debug_server",
        ":grpc_debug_test_server",
        ":hooks",
        ":local_cli_wrapper",
        "//tensorflow/python:util",
    ],
)

# Transitive dependencies of this target will be included in the pip package.
py_library(
    name = "debug_pip",
    data = [":grpc_tensorflow_server"],
    deps = [
        ":cli_test_utils",
        ":debug_py",
        ":grpc_debug_test_server",
        ":grpc_tensorflow_server_lib",
        ":offline_analyzer_lib",
        ":session_debug_testlib",
        ":source_remote",
    ],
)

py_library(
    name = "common",
    srcs = ["lib/common.py"],
    srcs_version = "PY2AND3",
)

py_library(
    name = "debug_graphs",
    srcs = ["lib/debug_graphs.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:framework",
        "//tensorflow/python:op_def_registry",
        "//tensorflow/python:platform",
        "//tensorflow/python:tensor_util",
        "@six_archive//:six",
    ],
)

py_library(
    name = "debug_data",
    srcs = ["lib/debug_data.py"],
    srcs_version = "PY2AND3",
    visibility = [
        "//tensorflow:internal",
        "//third_party/py/tf_slim:__subpackages__",
    ],
    deps = [
        ":debug_graphs",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:framework",
        "//tensorflow/python:op_def_registry",
        "//tensorflow/python:platform",
        "//tensorflow/python:tensor_util",
        "//third_party/py/numpy",
        "@six_archive//:six",
    ],
)

py_library(
    name = "debug_gradients",
    srcs = ["lib/debug_gradients.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":debug_data",
        ":debug_graphs",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:framework",
        "//tensorflow/python:platform",
        "@six_archive//:six",
    ],
)

py_library(
    name = "debug_utils",
    srcs = ["lib/debug_utils.py"],
    srcs_version = "PY2AND3",
)

py_binary(
    name = "grpc_tensorflow_server",
    srcs = ["lib/grpc_tensorflow_server.py"],
    python_version = "PY2",
    srcs_version = "PY2AND3",
    deps = [":grpc_tensorflow_server_lib"],
)

py_library(
    name = "grpc_tensorflow_server_lib",
    srcs = [
        "lib/grpc_tensorflow_server.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:platform",
        "//tensorflow/python:training",
    ],
)

py_library(
    name = "source_utils",
    srcs = ["lib/source_utils.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":profiling",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "source_remote",
    srcs = ["lib/source_remote.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":common",
        ":debug_service_pb2_grpc",
        "//tensorflow/core/debug:debug_service_proto_py",
        "//tensorflow/python/profiler:tfprof_logger",
    ],
)

py_library(
    name = "framework",
    srcs = ["wrappers/framework.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":debug_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:client",
        "//tensorflow/python:errors",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:training",
    ],
)

py_library(
    name = "debugger_cli_common",
    srcs = ["cli/debugger_cli_common.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:platform",
        "//third_party/py/numpy",
        "@six_archive//:six",
    ],
)

py_library(
    name = "cli_config",
    srcs = ["cli/cli_config.py"],
    srcs_version = "PY2AND3",
    deps = [":debugger_cli_common"],
)

py_library(
    name = "command_parser",
    srcs = ["cli/command_parser.py"],
    srcs_version = "PY2AND3",
)

py_library(
    name = "tensor_format",
    srcs = ["cli/tensor_format.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":debug_data",
        ":debugger_cli_common",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "cli_shared",
    srcs = ["cli/cli_shared.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":command_parser",
        ":common",
        ":debugger_cli_common",
        ":tensor_format",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:platform",
        "//tensorflow/python:variables",
        "//third_party/py/numpy",
        "@six_archive//:six",
    ],
)

py_library(
    name = "evaluator",
    srcs = ["cli/evaluator.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":debug_data",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "analyzer_cli",
    srcs = ["cli/analyzer_cli.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":cli_config",
        ":cli_shared",
        ":command_parser",
        ":debug_graphs",
        ":debugger_cli_common",
        ":evaluator",
        ":source_utils",
        ":ui_factory",
        "@six_archive//:six",
    ],
)

py_library(
    name = "profiling",
    srcs = ["lib/profiling.py"],
    srcs_version = "PY2AND3",
)

py_library(
    name = "profile_analyzer_cli",
    srcs = ["cli/profile_analyzer_cli.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":cli_shared",
        ":command_parser",
        ":debugger_cli_common",
        ":profiling",
        ":source_utils",
        ":ui_factory",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "base_ui",
    srcs = ["cli/base_ui.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":cli_config",
        ":command_parser",
        ":debugger_cli_common",
    ],
)

py_library(
    name = "curses_widgets",
    srcs = ["cli/curses_widgets.py"],
    srcs_version = "PY2AND3",
    deps = [":debugger_cli_common"],
)

py_library(
    name = "curses_ui",
    srcs = ["cli/curses_ui.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base_ui",
        ":cli_shared",
        ":command_parser",
        ":curses_widgets",
        ":debugger_cli_common",
        ":tensor_format",
        "@six_archive//:six",
    ],
)

py_library(
    name = "readline_ui",
    srcs = ["cli/readline_ui.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base_ui",
        ":debugger_cli_common",
    ],
)

py_library(
    name = "ui_factory",
    srcs = ["cli/ui_factory.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":curses_ui",
        ":readline_ui",
    ],
)

py_library(
    name = "dumping_wrapper",
    srcs = ["wrappers/dumping_wrapper.py"],
    srcs_version = "PY2AND3",
    visibility = [
        "//tensorflow:internal",
        "//third_party/py/tf_slim:__subpackages__",
    ],
    deps = [
        ":debug_data",
        ":framework",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:platform",
    ],
)

py_library(
    name = "grpc_wrapper",
    srcs = ["wrappers/grpc_wrapper.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":common",
        ":framework",
        ":source_remote",
    ],
)

py_library(
    name = "local_cli_wrapper",
    srcs = ["wrappers/local_cli_wrapper.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":analyzer_cli",
        ":cli_shared",
        ":command_parser",
        ":common",
        ":debug_data",
        ":debugger_cli_common",
        ":framework",
        ":profile_analyzer_cli",
        ":tensor_format",
        ":ui_factory",
    ],
)

py_library(
    name = "hooks",
    srcs = ["wrappers/hooks.py"],
    srcs_version = "PY2AND3",
    visibility = [
        "//tensorflow:internal",
        "//third_party/py/tf_slim:__subpackages__",
    ],
    deps = [
        ":debug_utils",
        ":dumping_wrapper",
        ":framework",
        ":grpc_wrapper",
        ":local_cli_wrapper",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:training",
    ],
)

py_binary(
    name = "offline_analyzer",
    srcs = ["cli/offline_analyzer.py"],
    python_version = "PY2",
    srcs_version = "PY2AND3",
    deps = [":offline_analyzer_lib"],
)

py_library(
    name = "offline_analyzer_lib",
    srcs = ["cli/offline_analyzer.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":analyzer_cli",
        ":debug_data",
        "//tensorflow/python",  # TODO(b/34059704): remove when fixed
        "//tensorflow/python:platform",
    ],
)

py_library(
    name = "debug_examples",
    deps = [
    ],
)

py_library(
    name = "session_debug_testlib",
    srcs = ["lib/session_debug_testlib.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":debug_data",
        ":debug_graphs",
        ":debug_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:client",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:data_flow_ops",
        "//tensorflow/python:errors",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:framework_test_lib",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:parsing_ops",
        "//tensorflow/python:platform_test",
        "//tensorflow/python:rnn",
        "//tensorflow/python:rnn_cell",
        "//tensorflow/python:state_ops",
        "//tensorflow/python:tensor_array_grad",
        "//tensorflow/python:training",
        "//tensorflow/python:variables",
        "//third_party/py/numpy",
        "@six_archive//:six",
    ],
)

py_library(
    name = "debug_service_pb2_grpc",
    srcs = ["lib/debug_service_pb2_grpc.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/core/debug:debug_service_proto_py",
    ],
)

py_library(
    name = "grpc_debug_server",
    srcs = ["lib/grpc_debug_server.py"],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        ":debug_graphs",
        ":debug_service_pb2_grpc",
        "//tensorflow/core/debug:debug_service_proto_py",
        "@six_archive//:six",
    ],
)

py_library(
    name = "grpc_debug_test_server",
    srcs = ["lib/grpc_debug_test_server.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":debug_data",
        ":debug_utils",
        ":grpc_debug_server",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:client",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:errors",
        "//tensorflow/python:variables",
    ],
)

py_library(
    name = "cli_test_utils",
    srcs = ["cli/cli_test_utils.py"],
    srcs_version = "PY2AND3",
)

