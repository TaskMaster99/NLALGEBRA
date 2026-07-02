cmake_minimum_required(VERSION 3.15)

project(NLA LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 12.2.0
)

FetchContent_MakeAvailable(fmt)

add_subdirectory(includes)
add_subdirectory(tests)