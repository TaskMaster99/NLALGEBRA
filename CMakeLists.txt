cmake_minimum_required(VERSION 3.20)

project(NLA LANGUAGES CXX ASM_NASM)
enable_language(ASM_NASM)
include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 12.2.0
)

FetchContent_MakeAvailable(fmt)

add_subdirectory(includes)
add_subdirectory(tests)