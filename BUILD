package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
    "envoy_cc_test",
    "envoy_cmake_external"
)

envoy_cmake_external(
    name = "dcmtk",
    cache_entries = {
        "CMAKE_CXX_COMPILER_FORCED": "on",
        "DCMTK_ENABLE_CXX11:BOOL": "TRUE",
        "DCMTK_ENABLE_STL:BOOL": "TRUE"
    },
    env_vars = { "CXX" : "g++" },
    lib_source = "@dcmtk//:all",
    alwayslink = 1,
    static_libraries = ["libdcmdsig.a", "libdcmiod.a", "libdcmpmap.a", "libdcmseg.a",
      "libdcmwlm.a", "libijg8.a", "libcharls.a", "libdcmfg.a", "libdcmjpeg.a", "libdcmpstat.a",
      "libdcmsr.a", "libi2d.a", "liboflog.a", "libcmr.a", "libdcmimage.a", "libdcmjpls.a", "libdcmqrdb.a",
      "libdcmtls.a", "libijg12.a", "libofstd.a", "libdcmdata.a", "libdcmimgle.a", "libdcmnet.a", "libdcmrt.a",
      "libdcmtract.a", "libijg16.a"],
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
            "@envoy//source/common/tcp_proxy",
            ":dcmtk"],
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
