add_library(nla.nla SHARED)

add_library(nla::nla ALIAS nla.nla)

set(LEVEL_1_HEADERS
    kernel/lvl1/dot.hpp
    kernel/lvl1/axpy.hpp
    utils.hpp   
)

set(LEVEL_1_SOURCES
    ${PROJECT_SOURCE_DIR}/src/kernel/lvl1/udot.asm
    ${PROJECT_SOURCE_DIR}/src/kernel/lvl1/uaxpy.asm
    ${PROJECT_SOURCE_DIR}/src/kernel/lvl1/uscal.asm   
)

set(INCLUDE_FILES
    ${LEVEL_1_HEADERS}
)

set(SRC_FILES
    ${LEVEL_1_SOURCES}
)

target_sources(nla.nla PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/includes FILES ${INCLUDE_FILES})
target_sources(nla.nla PRIVATE ${SRC_FILES})

target_compile_options(
    nla.nla
    INTERFACE -Wall -Wextra -Wpedantic -march=native -masm=intel -O3 -fPIC
)
target_link_libraries(nla.nla INTERFACE fmt::fmt)
set_target_properties(nla.nla PROPERTIES LINKER_LANGUAGE CXX)
