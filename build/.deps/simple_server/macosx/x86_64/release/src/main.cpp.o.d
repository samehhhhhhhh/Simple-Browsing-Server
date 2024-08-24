{
    files = {
        "src/main.cpp"
    },
    values = {
        "/Library/Developer/CommandLineTools/usr/bin/clang",
        {
            "-Qunused-arguments",
            "-isysroot",
            "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++17",
            "-Iincludes",
            "-DNDEBUG"
        }
    },
    depfiles_gcc = "build/.objs/simple_server/macosx/x86_64/release/src/__cpp_main.cpp.cpp:   src/main.cpp includes/includes.hpp includes/sqlite_handler.hpp   includes/algorithms.hpp\
"
}