# Copyright 2018 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================

# Description:
#   Contains the Keras Mixed Precision API (TensorFlow version).


package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "mixed_precision_experimental",
    srcs = ["__init__.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":loss_scale_optimizer",
        ":policy",
    ],
)

py_library(
    name = "policy",
    srcs = [
        "policy.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:framework",
        "//tensorflow/python:mixed_precision_global_state",
    ],
)

py_library(
    name = "autocast_variable",
    srcs = [
        "autocast_variable.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:framework",
        "//tensorflow/python:math_ops",
        "//tensorflow/python:resource_variable_ops",
        "//tensorflow/python/distribute:values",
        "//tensorflow/python/eager:context",
    ],
)

py_library(
    name = "loss_scale_optimizer",
    srcs = ["loss_scale_optimizer.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:loss_scale",
        "//tensorflow/python/keras/optimizer_v2",
        "@absl_py//absl/testing:parameterized",
    ],
)

py_library(
    name = "test_util",
    srcs = ["test_util.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:framework",
    ],
)

