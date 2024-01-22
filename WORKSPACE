workspace(name = "murtis_monovo")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

###############################
# murtis maintained external bazel projects
###############################
http_archive(
    name = "murtis_bazel_tools",
    sha256 = "099798213986aa96d7dc1bdc6f7b0841eeefe5408f6ede85f5530638a9aff1bf",
    strip_prefix = "bazel_tools-47f50405eb76f8320dc16c11509595254af98a4d",
    urls = ["https://github.com/curtismuntz/bazel_tools/archive/47f50405eb76f8320dc16c11509595254af98a4d.tar.gz"],
)

load("@murtis_bazel_tools//tools:github_repo.bzl", "github_repo")
load("@murtis_bazel_tools//tools:deps.bzl", "google_cpp_dependencies", "linter_dependencies")

linter_dependencies()

http_archive(
    name = "murtis_bazel_compilers",
    sha256 = "16865fc175a3f64f5179c484d47b80170e7635093348ce51743c1eb261413246",
    strip_prefix = "bazel_compilers-0.4.0",
    urls = ["https://github.com/curtismuntz/bazel_compilers/archive/v0.4.0.tar.gz"],
)

load("@murtis_bazel_compilers//compilers:dependencies.bzl", "cross_compiler_dependencies")

cross_compiler_dependencies()

###############################
# c++
###############################
http_archive(
    name = "opencv_archive",
    build_file = "//third_party:opencv.BUILD",
    sha256 = "f3b160b9213dd17aa15ddd45f6fb06017fe205359dbd1f7219aad59c98899f15",
    strip_prefix = "opencv-3.1.0",
    url = "https://github.com/opencv/opencv/archive/3.1.0.tar.gz",
)

http_archive(
    name = "libjpeg_archive",
    build_file = "//third_party:jpeg.BUILD",
    sha256 = "75c3ec241e9996504fe02a9ed4d12f16b74ade713972f3db9e65ce95cd27e35d",
    strip_prefix = "jpeg-6b",
    urls = [
        "https://svwh.dl.sourceforge.net/project/libjpeg/libjpeg/6b/jpegsrc.v6b.tar.gz",
    ],
)

http_archive(
    name = "libpng_archive",
    build_file = "//third_party:png.BUILD",
    sha256 = "e30bf36cd5882e017c23a5c6a79a9aa1a744dd5841bb45ff7035ec6e3b3096b8",
    strip_prefix = "libpng-1.6.29",
    url = "http://download.sourceforge.net/libpng/libpng-1.6.29.tar.gz",
)

bind(
    name = "png",
    actual = "@libpng_archive//:libpng",
)

http_archive(
    name = "zlib_git",
    build_file = "//third_party:zlib.BUILD",
    sha256 = "17e88863f3600672ab49182f217281b6fc4d3c762bde361935e436a95214d05c",
    strip_prefix = "zlib-1.3.1",
    url = "https://github.com/madler/zlib/archive/v1.3.1.tar.gz",
)

bind(
    name = "myzlib",
    actual = "@zlib_git//:zlib",
)

http_archive(
    name = "com_github_ben-strasser_fast-cpp-csv-parser",
    build_file = "//third_party:fast-cpp-csv-parser.BUILD",
    strip_prefix = "fast-cpp-csv-parser-78f413248fdeea27368481c4a1d48c059ac36680",
    # sha256 = "",
    url = "https://github.com/ben-strasser/fast-cpp-csv-parser/archive/78f413248fdeea27368481c4a1d48c059ac36680.tar.gz",
)

###############################
# protobuf
###############################
http_archive(
    name = "build_stack_rules_proto",
    sha256 = "9c9fc051189dd87bd643cf69e82e3b08de03114fc03155de784ba60bd0cef4b6",
    strip_prefix = "rules_proto-609362dd9b08110b7a95bfa26b5e3aac3cd06905",
    urls = ["https://github.com/stackb/rules_proto/archive/609362dd9b08110b7a95bfa26b5e3aac3cd06905.tar.gz"],
)

load("@build_stack_rules_proto//cpp:deps.bzl", "cpp_grpc_library")

cpp_grpc_library()

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

###############################
# Buildifier
# This section allows buildifier to exist as part of the bazel project. Simply run the following
# command to run buildifier on all bazel BUILD/starlark targets.
# bazel run //:buildifier
###############################
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# buildifier is written in Go and hence needs rules_go to be built.
# See https://github.com/bazelbuild/rules_go for the up to date setup instructions.
http_archive(
    name = "io_bazel_rules_go",
    sha256 = "ade51a315fa17347e5c31201fdc55aa5ffb913377aa315dceb56ee9725e620ee",
    url = "https://github.com/bazelbuild/rules_go/releases/download/0.16.6/rules_go-0.16.6.tar.gz",
)

http_archive(
    name = "com_github_bazelbuild_buildtools",
    sha256 = "e8792ae37bfa82eb4efa3e2d93a5b4dcc43d681d13f6d00f183d2ef34a4bc828",
    strip_prefix = "buildtools-4bcdbd1064fcc48180fa30400e39f7a940fdb8f9",
    url = "https://github.com/bazelbuild/buildtools/archive/4bcdbd1064fcc48180fa30400e39f7a940fdb8f9.zip",
)

load("@io_bazel_rules_go//go:def.bzl", "go_register_toolchains", "go_rules_dependencies")
load("@com_github_bazelbuild_buildtools//buildifier:deps.bzl", "buildifier_dependencies")

go_rules_dependencies()

go_register_toolchains()

buildifier_dependencies()

###############################
# rust
###############################
http_archive(
    name = "io_bazel_rules_rust",
    sha256 = "c82118824b2448b77146f1dae97b6eaa717babedad0822aca4879f3cbbf2b7b5",
    strip_prefix = "rules_rust-3228ccd3814c2ad0d7307d2f87fb8ff9616149d7",
    urls = [
        # Master branch as of 2018-12-11
        "https://github.com/bazelbuild/rules_rust/archive/3228ccd3814c2ad0d7307d2f87fb8ff9616149d7.tar.gz",
    ],
)

http_archive(
    name = "libc",
    build_file = "@//:libc.BUILD",
    sha256 = "1ac4c2ac6ed5a8fb9020c166bc63316205f1dc78d4b964ad31f4f21eb73f0c6d",
    strip_prefix = "libc-0.2.20",
    urls = [
        "https://mirror.bazel.build/github.com/rust-lang/libc/archive/0.2.20.zip",
        "https://github.com/rust-lang/libc/archive/0.2.20.zip",
    ],
)

http_archive(
    name = "bazel_skylib",
    sha256 = "eb5c57e4c12e68c0c20bc774bfbc60a568e800d025557bc4ea022c6479acc867",
    strip_prefix = "bazel-skylib-0.6.0",
    url = "https://github.com/bazelbuild/bazel-skylib/archive/0.6.0.tar.gz",
)

load("@io_bazel_rules_rust//rust:repositories.bzl", "rust_repositories")

rust_repositories()

load("@io_bazel_rules_rust//:workspace.bzl", "bazel_version")

bazel_version(name = "bazel_version")
