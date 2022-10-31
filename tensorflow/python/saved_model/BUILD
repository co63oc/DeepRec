# Description:
# TensorFlow SavedModel.


package(
    # TODO(drpng): change that to //third_party/tensorflow:internal
    # when we have migrated all users.
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "saved_model",
    srcs = ["saved_model.py"],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:internal"],
    deps = [
        ":builder",
        ":constants",
        ":load",
        ":loader",
        ":main_op",
        ":save",
        ":signature_constants",
        ":signature_def_utils",
        ":simple_save",
        ":tag_constants",
        ":utils",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "constants",
    srcs = ["constants.py"],
    srcs_version = "PY2AND3",
    deps = ["//tensorflow/python:util"],
)

py_library(
    name = "signature_constants",
    srcs = ["signature_constants.py"],
    srcs_version = "PY2AND3",
    deps = ["//tensorflow/python:util"],
)

py_library(
    name = "tag_constants",
    srcs = ["tag_constants.py"],
    srcs_version = "PY2AND3",
    deps = ["//tensorflow/python:util"],
)

py_library(
    name = "builder",
    srcs = [
        "builder.py",
        "builder_impl.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":constants",
        ":utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:lib",
        "//tensorflow/python:platform",
        "//tensorflow/python:saver",
        "//tensorflow/python:util",
        "//tensorflow/python:variables",
    ],
)

py_library(
    name = "loader",
    srcs = [
        "loader.py",
        "loader_impl.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":constants",
        ":signature_def_utils",
        ":utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:lib",
        "//tensorflow/python:platform",
        "//tensorflow/python:saver",
        "//tensorflow/python:util",
        "//tensorflow/python:variables",
    ],
)

py_library(
    name = "simple_save",
    srcs = [
        "simple_save.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":builder",
        ":signature_constants",
        ":signature_def_utils",
        ":tag_constants",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:lib",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "main_op",
    srcs = [
        "main_op.py",
        "main_op_impl.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:lookup_ops",
        "//tensorflow/python:util",
        "//tensorflow/python:variables",
    ],
)

py_library(
    name = "utils",
    srcs = [
        "utils.py",
        "utils_impl.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":constants",
        ":nested_structure_coder",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:framework_for_generated_wrappers",
        "//tensorflow/python:lib",
        "//tensorflow/python:sparse_tensor",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "signature_def_utils",
    srcs = [
        "signature_def_utils.py",
        "signature_def_utils_impl.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":signature_constants",
        ":utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "signature_serialization",
    srcs = [
        "signature_serialization.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":revived_types",
        ":signature_constants",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:tensor_spec",
        "//tensorflow/python:util",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/eager:function",
        "//tensorflow/python/training/tracking:base",
    ],
)

py_library(
    name = "save",
    srcs = [
        "save.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":builder",
        ":constants",
        ":function_serialization",
        ":nested_structure_coder",
        ":revived_types",
        ":signature_constants",
        ":signature_def_utils",
        ":signature_serialization",
        ":tag_constants",
        ":utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:lib",
        "//tensorflow/python:resource_variable_ops",
        "//tensorflow/python:util",
        "//tensorflow/python/eager:context",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/eager:function",
        "//tensorflow/python/training/saving:functional_saver",
        "//tensorflow/python/training/tracking",
        "//tensorflow/python/training/tracking:base",
        "//tensorflow/python/training/tracking:graph_view",
        "//tensorflow/python/training/tracking:util",
    ],
)

py_library(
    name = "load",
    srcs = [
        "load.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":constants",
        ":function_deserialization",
        ":load_v1_in_v2",
        ":loader",
        ":nested_structure_coder",
        ":revived_types",
        ":utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:init_ops",
        "//tensorflow/python:lib",
        "//tensorflow/python:resource_variable_ops",
        "//tensorflow/python:tensor_util",
        "//tensorflow/python:util",
        "//tensorflow/python:variables",
        "//tensorflow/python/distribute:distribute_lib",
        "//tensorflow/python/distribute:values",
        "//tensorflow/python/training/tracking",
        "//tensorflow/python/training/tracking:base",
        "//tensorflow/python/training/tracking:graph_view",
        "//tensorflow/python/training/tracking:util",
    ],
)

py_library(
    name = "load_v1_in_v2",
    srcs = [
        "load_v1_in_v2.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":loader",
        ":signature_serialization",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:saver",
        "//tensorflow/python/eager:wrap_function",
        "//tensorflow/python/training/tracking",
    ],
)

py_library(
    name = "revived_types",
    srcs = [
        "revived_types.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/core:protos_all_py",
    ],
)

py_library(
    name = "function_serialization",
    srcs = [
        "function_serialization.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":nested_structure_coder",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/eager:function",
    ],
)

py_library(
    name = "function_deserialization",
    srcs = [
        "function_deserialization.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":nested_structure_coder",
        "//tensorflow/python/eager:def_function",
    ],
)

py_library(
    name = "nested_structure_coder",
    srcs = ["nested_structure_coder.py"],
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:framework",
        "//tensorflow/python:tensor_array_ops",
        "//tensorflow/python/data/ops:dataset_ops",
        "//tensorflow/python/data/ops:iterator_ops",
        "//tensorflow/python/data/ops:optional_ops",
        "//tensorflow/python/distribute:values",
        "//tensorflow/python/ops/ragged",
        "@six_archive//:six",
    ],
)

