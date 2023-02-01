cmake_minimum_required(VERSION 3.25.2)
project(my_utils VERSION 1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(my_utils SHARED src/random.cpp)

target_include_directories(my_utils PRIVATE include)

set_target_properties(
    my_utils
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER include/my_utils.h
)

include(GNUInstallDirs)

install(
    TARGETS my_utils
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
