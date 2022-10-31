# Copyright 2016 The TensorFlow Authors. All Rights Reserved.
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
#   Keras saving and loading libraries.

package(
    default_visibility = ["//tensorflow:__subpackages__"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["LICENSE"])

py_library(
    name = "model_utils",
    srcs = ["__init__.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":export_output",
        ":export_utils",
        ":mode_keys",
    ],
)

py_library(
    name = "export_output",
    srcs = ["export_output.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:constant_op",
        "//tensorflow/python:dtypes",
        "//tensorflow/python:framework_ops",
        "//tensorflow/python/saved_model:signature_def_utils",
    ],
)

py_library(
    name = "export_utils",
    srcs = ["export_utils.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":export_output",
        ":mode_keys",
        "//tensorflow/python:platform",
        "//tensorflow/python:util",
        "//tensorflow/python/saved_model:signature_constants",
        "//tensorflow/python/saved_model:signature_def_utils",
        "//tensorflow/python/saved_model:tag_constants",
    ],
)

py_library(
    name = "mode_keys",
    srcs = ["mode_keys.py"],
    srcs_version = "PY2AND3",
)


