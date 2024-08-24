add_rules("mode.debug", "mode.release")
add_requires("sqlite3")
target("simple_server")

    set_kind("binary")
    add_includedirs("includes")
    add_files("src/*.cpp")
    add_links("sqlite3")
    set_languages("c++17")
    

