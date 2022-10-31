
package(
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

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
    name = "pyct",
    srcs = [
        "__init__.py",
        "anno.py",
        "ast_util.py",
        "cfg.py",
        "compiler.py",
        "errors.py",
        "gast_util.py",
        "inspect_utils.py",
        "origin_info.py",
        "parser.py",
        "pretty_printer.py",
        "qual_names.py",
        "templates.py",
        "transformer.py",
    ],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow/python/autograph/pyct/common_transformers",
        "@astunparse_archive//:astunparse",
        "@gast_archive//:gast",
        "@six_archive//:six",
        "@termcolor_archive//:termcolor",
    ],
)

sh_test(
    name = "inspect_utils_test_par",
    srcs = ["inspect_utils_test.sh"],
    tags = ["no_oss"],
)

