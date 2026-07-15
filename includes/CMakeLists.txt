add_library(nla.nla SHARED)

add_library(nla::nla ALIAS nla.nla)

set(INCLUDE_FILES
    kernel/dot.hpp
    kernel/axpy.hpp
    kernel/utils.hpp
)


target_sources(nla.nla PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/includes FILES ${INCLUDE_FILES})
target_sources(nla.nla PRIVATE ${CMAKE_SOURCE_DIR}/includes/kernel/udot.asm)
target_sources(nla.nla PRIVATE ${CMAKE_SOURCE_DIR}/includes/kernel/uaxpy.asm)

target_compile_options(
    nla.nla
    INTERFACE -Wall -Wextra -Wpedantic -march=native -masm=intel -O3 -fPIC
)
target_link_libraries(nla.nla INTERFACE fmt::fmt)
set_target_properties(nla.nla PROPERTIES LINKER_LANGUAGE CXX)
