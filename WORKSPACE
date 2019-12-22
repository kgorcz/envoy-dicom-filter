workspace(name = "envoy_dicom_filter")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

local_repository(
     name = "envoy",
     path = "envoy",
)

load("@envoy//bazel:api_binding.bzl", "envoy_api_binding")

envoy_api_binding()

load("@envoy//bazel:api_repositories.bzl", "envoy_api_dependencies")

envoy_api_dependencies()

load("@envoy//bazel:repositories.bzl", "envoy_dependencies")

envoy_dependencies()

load("@envoy//bazel:dependency_imports.bzl", "envoy_dependency_imports")

envoy_dependency_imports()

# http_archive(
#     name = "rules_foreign_cc",
#     sha256 = "3184c244b32e65637a74213fc448964b687390eeeca42a36286f874c046bba15",
#     strip_prefix = "rules_foreign_cc-7bc4be735b0560289f6b86ab6136ee25d20b65b7",
#     # 2019-09-26
#     urls = ["https://github.com/bazelbuild/rules_foreign_cc/archive/7bc4be735b0560289f6b86ab6136ee25d20b65b7.tar.gz"],
# )
# load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
# rules_foreign_cc_dependencies()

# https://docs.bazel.build/versions/master/be/workspace.html#new_http_archive
http_archive(
    name = "dcmtk",	# Reference as @dcmtk//:target-lib
    urls = ["https://github.com/DCMTK/dcmtk/archive/DCMTK-3.6.5.zip"],
    sha256 = "90a3361c26e5107c567025566ce2bc457adad4801026dfd7898dafc07152c907",
    build_file_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])""",
    strip_prefix = "dcmtk-DCMTK-3.6.5",
    #build_file = "@//:dcmtk.BUILD",
)
