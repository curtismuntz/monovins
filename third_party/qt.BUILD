cc_library(
    name = "qt_core",
    hdrs = glob(["QtCore/**"]),
    includes = [
        ".",
        "QtCore",
    ],
    linkopts = ["-lQt5Core"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "qt_widgets",
    hdrs = glob(["QtWidgets/**"]),
    includes = [
        ".",
        "QtWidgets",
    ],
    linkopts = ["-lQt5Widgets"],
    visibility = ["//visibility:public"],
    deps = [
        ":qt_core",
        ":qt_gui",
    ],
)

cc_library(
    name = "qt_gui",
    hdrs = glob(["QtGui/**"]),
    includes = [
      ".",
      "QtGui"
    ],
    linkopts = ["-lQt5Gui"],
    visibility = ["//visibility:public"],
    deps = [":qt_core"],
)

cc_library(
    name = "qt_concurrent",
    hdrs = glob(["QtConcurrent/**"]),
    includes = [
      ".",
      "QtConcurrent",
    ],
    linkopts = ["-lQt5Concurrent"],
    visibility = ["//visibility:public"],
    deps = [":qt_core"],
)

cc_library(
    name = "qt_test",
    hdrs = glob(["QtTest/**"]),
    includes = [
      ".",
      "QtTest",
    ],
    linkopts = ["-lQt5Test"],
    visibility = ["//visibility:public"],
    deps = [":qt_core"],
)

cc_library(
    name = "qt_opengl",
    hdrs = glob(["QtOpenGL/**"]),
    includes = [
      ".",
      "QtOpenGL",
    ],
    linkopts = ["-lQt5OpenGL"],
    visibility = ["//visibility:public"],
    deps = [":qt_core"],
)
