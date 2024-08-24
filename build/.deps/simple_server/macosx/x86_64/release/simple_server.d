{
    files = {
        "build/.objs/simple_server/macosx/x86_64/release/src/algorithms.cpp.o",
        "build/.objs/simple_server/macosx/x86_64/release/src/sql_process_requests.cpp.o",
        "build/.objs/simple_server/macosx/x86_64/release/src/insert_tables.cpp.o",
        "build/.objs/simple_server/macosx/x86_64/release/src/main.cpp.o"
    },
    values = {
        "/Library/Developer/CommandLineTools/usr/bin/clang++",
        {
            "-isysroot",
            "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk",
            "-lz",
            "-Wl,-x",
            "-Wl,-dead_strip",
            "-lsqlite3"
        }
    }
}