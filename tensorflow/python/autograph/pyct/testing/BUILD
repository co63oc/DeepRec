
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
    name = "testing",
    srcs = [
        "basic_definitions.py",
        "decorators.py",
    ],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
)

py_library(
    name = "codegen",
    srcs = [
        "codegen.py",
    ],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow/python/autograph/pyct",
        "//tensorflow/python/autograph/utils",
        "@gast_archive//:gast",
    ],
)


