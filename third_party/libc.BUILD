# from https://github.com/bazelbuild/rules_rust/blob/master/examples/libc.BUILD
load("@io_bazel_rules_rust//rust:rust.bzl", "rust_library")

rust_library(
    name = "libc",
    srcs = glob(["src/**/*.rs"]),
    visibility = ["//visibility:public"],
)
