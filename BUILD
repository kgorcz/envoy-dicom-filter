package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
    "envoy_cc_test",
)

envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        ":dicom_config",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)

envoy_cc_library(
    name = "dicom_lib",
    srcs = ["dicom.cc"],
    hdrs = ["dicom.h"],
    repository = "@envoy",
    deps = ["@envoy//include/envoy/network:filter_interface",
            "@envoy//include/envoy/network:connection_interface",
            "@envoy//source/common/common:minimal_logger_lib",
            "@envoy//source/common/tcp_proxy"],
)

envoy_cc_library(
    name = "dicom_config",
    srcs = ["dicom_config.cc"],
    repository = "@envoy",
    deps = [
        ":dicom_lib",
        "@envoy//include/envoy/network:filter_interface",
        "@envoy//include/envoy/registry:registry",
        "@envoy//include/envoy/server:filter_config_interface",
    ],
)

sh_test(
    name = "envoy_binary_test",
    srcs = ["envoy_binary_test.sh"],
    data = [":envoy"],
)
