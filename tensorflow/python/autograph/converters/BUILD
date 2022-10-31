
package(
    licenses = ["notice"],  # Apache 2.0
)

filegroup(
    name = "all_files",
    srcs = glob(
        ["**/*"],
        exclude = [
            "**/METADATA",
            "**/OWNERS",
        ],
    ),
    visibility = ["//tensorflow:__subpackages__"],
)

py_library(
    name = "converters",
    srcs = [
        "arg_defaults.py",
        "asserts.py",
        "break_statements.py",
        "call_trees.py",
        "conditional_expressions.py",
        "continue_statements.py",
        "control_flow.py",
        "directives.py",
        "function_scopes.py",
        "list_comprehensions.py",
        "lists.py",
        "logical_expressions.py",
        "return_statements.py",
        "slices.py",
    ],
    srcs_version = "PY2AND3",
    visibility = ["//tensorflow:__subpackages__"],
    deps = [
        "//tensorflow/python:util",
        "//tensorflow/python/autograph/core",
        "//tensorflow/python/autograph/lang",
        "//tensorflow/python/autograph/pyct",
        "//tensorflow/python/autograph/pyct/static_analysis",
        "@gast_archive//:gast",
    ],
)

