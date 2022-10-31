
package(
    licenses = ["notice"],  # Apache 2.0
)

# NOTE: Do not add sharding to these tests. If tests run concurrently, they
# seem to confuse the memory_profiler, and the tests begin to flake. Add new
# test files as needed.

py_library(
    name = "memory_test_util",
    srcs = ["memory_test_util.py"],
    visibility = ["//tensorflow:internal"],
    deps = ["@six_archive//:six"],
)

