add_library(nla.nla INTERFACE)

add_library(nla::nla ALIAS nla.nla)

set(INCLUDE_FILES
    nla_tools.hpp
    nla_kernels/kernels.hpp
    nla_structures/matrix.hpp
    nla_structures/vector.hpp
)

target_sources(nla.nla INTERFACE FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/includes FILES ${INCLUDE_FILES})

target_compile_options(
    nla.nla
    INTERFACE -Wall -Wextra -Wpedantic -O3 -march=native
)
target_link_libraries(nla.nla INTERFACE fmt::fmt)