#bazel build  -c opt --config=opt  --config=mkl_threadpool --define build_with_mkl_dnn_v1_only=true --verbose_failures //tensorflow/compiler/xla/service:platform_util
bazel build  -c opt --config=opt  --config=mkl_threadpool --define build_with_mkl_dnn_v1_only=true --verbose_failures //tensorflow/tools/pip_package:build_pip_package \
&& ./bazel-bin/tensorflow/tools/pip_package/build_pip_package /tmp/tensorflow_pkg_2
