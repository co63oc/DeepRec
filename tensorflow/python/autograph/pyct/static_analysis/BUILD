
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
    name = "static_analysis",
    srcs = [
        "activity.py",
        "annos.py",
        "liveness.py",
        "reaching_definitions.py",
    ],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow/python:util",
        "//tensorflow/python/autograph/pyct",
        "//tensorflow/python/autograph/utils",
        "@gast_archive//:gast",
    ],
)

py_library(
    name = "activity_test_lib",
    testonly = True,
    srcs = ["activity_test.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":static_analysis",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python/autograph/pyct",
        "@gast_archive//:gast",
    ],
)



py_library(
    name = "liveness_test_lib",
    srcs = ["liveness_test.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":static_analysis",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python/autograph/pyct",
        "@gast_archive//:gast",
    ],
)



py_library(
    name = "reaching_definitions_test_lib",
    srcs = ["reaching_definitions_test.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":static_analysis",
        "//tensorflow/python:client_testlib",
        "//tensorflow/python/autograph/pyct",
        "@gast_archive//:gast",
    ],
)


