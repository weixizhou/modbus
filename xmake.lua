add_requires("libmodbus")

target("modbus")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("libmodbus")
    add_includedirs("include")
    set_targetdir("$(projectdir)/build/bin")