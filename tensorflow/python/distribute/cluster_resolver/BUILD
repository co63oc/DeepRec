# Description: Operations defined for Cluster Resolvers

load(
    "//tensorflow/core/platform:default/build_config.bzl",
    "tf_additional_rpc_deps",
)

package(
    default_visibility = [
        "//tensorflow:__subpackages__",
    ],
    licenses = ["notice"],  # Apache 2.0
)

py_library(
    name = "cluster_resolver_lib",
    srcs = [
        "__init__.py",
    ],
    srcs_version = "PY2AND3",
    visibility = ["//visibility:public"],
    deps = [
        ":base_cluster_resolver_py",
        ":gce_cluster_resolver_py",
        ":kubernetes_cluster_resolver_py",
        ":slurm_cluster_resolver_py",
        ":tfconfig_cluster_resolver_py",
        "//tensorflow/python:util",
    ],
)

py_library(
    name = "base_cluster_resolver_py",
    srcs = ["cluster_resolver.py"],
    srcs_version = "PY2AND3",
    deps = [
        "//tensorflow/python:training_server_lib",
    ],
)

py_library(
    name = "gce_cluster_resolver_py",
    srcs = ["gce_cluster_resolver.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base_cluster_resolver_py",
        "//tensorflow/python:training_server_lib",
    ],
)

py_library(
    name = "tfconfig_cluster_resolver_py",
    srcs = ["tfconfig_cluster_resolver.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base_cluster_resolver_py",
        "//tensorflow/python:training_server_lib",
    ],
)

py_library(
    name = "slurm_cluster_resolver_py",
    srcs = ["slurm_cluster_resolver.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base_cluster_resolver_py",
        "//tensorflow/python:training_server_lib",
    ],
)

py_library(
    name = "kubernetes_cluster_resolver_py",
    srcs = ["kubernetes_cluster_resolver.py"],
    srcs_version = "PY2AND3",
    deps = [
        ":base_cluster_resolver_py",
        "//tensorflow/python:training_server_lib",
    ],
)

