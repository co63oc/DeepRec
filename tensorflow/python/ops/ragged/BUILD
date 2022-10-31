
package(
    default_visibility = [
        "//intelligence/datum/prensor:__pkg__",
        "//learning/brain/contrib/text:__pkg__",
        "//nlp/nlx/bert:__pkg__",
        "//nlp/projects/atc/tf/ops:__pkg__",
        "//tensorflow:internal",
    ],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

#-------------------------------------------------------------------------------
# RaggedTensor
#-------------------------------------------------------------------------------

py_library(
    name = "ragged",
    srcs = ["__init__.py"],
    srcs_version = "PY2AND3",
    tags = ["nofixdeps"],
    deps = [
        ":ragged_array_ops",
        ":ragged_batch_gather_ops",
        ":ragged_batch_gather_with_default_op",
        ":ragged_concat_ops",
        ":ragged_config",
        ":ragged_conversion_ops",
        ":ragged_dispatch",
        ":ragged_factory_ops",
        ":ragged_functional_ops",
        ":ragged_gather_ops",
        ":ragged_getitem",
        ":ragged_map_ops",
        ":ragged_math_ops",
        ":ragged_operators",
        ":ragged_string_ops",
        ":ragged_tensor",
        ":ragged_tensor_shape",
        ":ragged_tensor_value",
        ":ragged_util",
        ":ragged_where_op",
        ":segment_id_ops",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "ragged_array_ops",
    srcs = ["ragged_array_ops.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_functional_ops",
        ":ragged_math_ops",
        ":ragged_tensor",
        ":ragged_util",
        ":segment_id_ops",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:sort_ops",
        "//tensorflow/python:tensor_util",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "ragged_batch_gather_ops",
    srcs = ["ragged_batch_gather_ops.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_gather_ops",
        ":ragged_tensor",
        ":ragged_util",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:check_ops",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
    ],
)

py_library(
    name = "ragged_batch_gather_with_default_op",
    srcs = [
        "ragged_batch_gather_with_default_op.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_array_ops",
        ":ragged_dispatch",
        ":ragged_operators",
        ":ragged_tensor",
        ":ragged_tensor_shape",
        ":ragged_where_op",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:check_ops",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
    ],
)

py_library(
    name = "ragged_concat_ops",
    srcs = ["ragged_concat_ops.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_array_ops",
        ":ragged_gather_ops",
        ":ragged_tensor",
        ":ragged_util",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:check_ops",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:tensor_shape",
    ],
)

py_library(
    name = "ragged_conversion_ops",
    srcs = ["ragged_conversion_ops.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_tensor",
        "//tensorflow/python:dtypes",
    ],
)

py_library(
    name = "ragged_factory_ops",
    srcs = ["ragged_factory_ops.py"],
    deps = [
        ":ragged_tensor",
        ":ragged_tensor_value",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:util",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "ragged_functional_ops",
    srcs = ["ragged_functional_ops.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_config",
        ":ragged_tensor",
        ":ragged_util",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "ragged_gather_ops",
    srcs = ["ragged_gather_ops.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_array_ops",
        ":ragged_tensor",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:ragged_array_ops_gen",
        "//tensorflow/python:tensor_shape",
    ],
)

py_library(
    name = "ragged_getitem",
    srcs = ["ragged_getitem.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_gather_ops",
        ":ragged_math_ops",
        ":ragged_tensor",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python/eager:context",
    ],
)

py_library(
    name = "ragged_math_ops",
    srcs = ["ragged_math_ops.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_functional_ops",
        ":ragged_tensor",
        ":ragged_util",
        ":segment_id_ops",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:check_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:ragged_math_ops_gen",
        "//tensorflow/python:tensor_util",
        "//tensorflow/python:util",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "ragged_operators",
    srcs = ["ragged_operators.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_getitem",
        ":ragged_tensor",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "ragged_string_ops",
    srcs = ["ragged_string_ops.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_array_ops",
        ":ragged_math_ops",
        ":ragged_tensor",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:string_ops",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "ragged_squeeze_op",
    srcs = ["ragged_squeeze_op.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_tensor",
        ":ragged_util",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
    ],
)

py_library(
    name = "ragged_config",
    srcs = ["ragged_config.py"],
    srcs_version = "PY2AND3",
)

py_library(
    name = "ragged_tensor",
    srcs = ["ragged_tensor.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_config",
        ":ragged_tensor_value",
        ":ragged_util",
        ":segment_id_ops",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:check_ops",
        "//tensorflow/python:composite_tensor",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:ragged_conversion_ops_gen",
        "//tensorflow/python:session",
        "//tensorflow/python:sparse_tensor",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:tensor_spec",
        "//tensorflow/python:tensor_util",
        "//tensorflow/python:type_spec",
        "//tensorflow/python:util",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "ragged_tensor_shape",
    srcs = ["ragged_tensor_shape.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_array_ops",
        ":ragged_config",
        ":ragged_tensor",
        ":ragged_util",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:tensor_util",
    ],
)

py_library(
    name = "ragged_tensor_value",
    srcs = ["ragged_tensor_value.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:util",
        "//third_party/py/numpy",
    ],
)

py_library(
    name = "ragged_util",
    srcs = ["ragged_util.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:array_ops",
        "//tensorflow/python:check_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:ragged_math_ops_gen",
    ],
)

py_library(
    name = "ragged_where_op",
    srcs = ["ragged_where_op.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_concat_ops",
        ":ragged_functional_ops",
        ":ragged_gather_ops",
        ":ragged_tensor",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
    ],
)

py_library(
    name = "segment_id_ops",
    srcs = ["segment_id_ops.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_util",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:tensor_util",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "ragged_map_ops",
    srcs = ["ragged_map_ops.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_config",
        ":ragged_tensor",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:constant_op",
        "//tensorflow/python:control_flow_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:platform",
        "//tensorflow/python:sparse_tensor",
        "//tensorflow/python:tensor_array_ops",
        "//tensorflow/python:tensor_shape",
        "//tensorflow/python:util",
        "//tensorflow/python:variable_scope",
        "//tensorflow/python/eager:context",
    ],
)

py_library(
    name = "ragged_dispatch",
    srcs = ["ragged_dispatch.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":ragged_array_ops",
        ":ragged_batch_gather_ops",
        ":ragged_concat_ops",
        ":ragged_gather_ops",
        ":ragged_math_ops",
        ":ragged_squeeze_op",
        ":ragged_tensor",
        ":ragged_tensor_shape",
        ":ragged_util",
        ":ragged_where_op",
        "//tensorflow/python:array_ops",
        "//tensorflow/python:bitwise_ops",
        "//tensorflow/python:clip_ops",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:parsing_ops",
        "//tensorflow/python:sparse_tensor",
        "//tensorflow/python:string_ops",
        "//tensorflow/python:util",
        "//tensorflow/python:variables",
        "//third_party/py/numpy",
    ],
)

#-------------------------------------------------------------------------------
# RaggedTensor Tests
#-------------------------------------------------------------------------------


