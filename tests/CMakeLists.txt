
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.15.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(test)
target_sources(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

target_link_libraries(test PRIVATE nla::nla Catch2::Catch2WithMain)

set(COMPILE_OPTIONS -Wall -Wextra -g)

target_compile_options(test PRIVATE ${COMPILE_OPTIONS})