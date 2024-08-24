{
    depfiles_gcc = "build/.objs/simple_server/macosx/x86_64/release/src/__cpp_sql_process_requests.cpp.cpp:   src/sql_process_requests.cpp includes/sqlite_handler.hpp   includes/includes.hpp\
",
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
    files = {
        "src/sql_process_requests.cpp"
    }
}