# Tests of TensorFlow kernels written using the Python API.

package(
    default_visibility = ["//tensorflow:internal"],
    licenses = ["notice"],  # Apache 2.0
)

# CPU only tests should use tf_py_test, GPU tests use cuda_py_test
# Please avoid the py_tests and cuda_py_tests (plural) while we
# fix the shared/overbroad dependencies.

py_library(
    name = "util",
    srcs = ["util.py"],
    deps = [
        "//third_party/py/numpy",
    ],
)

