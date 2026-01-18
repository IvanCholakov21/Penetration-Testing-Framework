cmake_minimum_required(VERSION 3.10)
project(pentest_framework)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR})


add_executable(pentest
    main.cpp
    core/network.h
    core/network.cpp
    core/module.h
    core/module_manager.h
    core/logger.cpp
    modules/portscan.cpp
    modules/banner_grab.cpp
    modules/fuzzer.cpp
    )
