cmake_minimum_required(VERSION 3.22)
project(my_utils VERSION 0.1)

# c++ VERSION 20
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES main.cpp random.cpp unsignedCast.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

set(WARNINGS
    -Weverything
    -Wno-string-compare
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        ${WARNINGS}
        -fsanitize=address
        -fsanitize=undefined
        -fno-sanitize-recover=all
)

target_link_options(
    ${PROJECT_NAME}
    PRIVATE -fsanitize=address -fsanitize=undefined
)
