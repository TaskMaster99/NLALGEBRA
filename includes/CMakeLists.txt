add_library(nla.nla SHARED)

add_library(nla::nla ALIAS nla.nla)

set(BLAS_1_HEADERS
    kernel/blas1/dot.hpp
    kernel/blas1/axpy.hpp
    kernel/blas1/scal.hpp
    kernel/blas1/copy.hpp
    kernel/blas1/swap.hpp

    utils.hpp   
)

set(BLAS_1_SOURCES
    ${PROJECT_SOURCE_DIR}/src/kernel/blas1/udot.asm
    ${PROJECT_SOURCE_DIR}/src/kernel/blas1/uaxpy.asm
    ${PROJECT_SOURCE_DIR}/src/kernel/blas1/uscal.asm
    ${PROJECT_SOURCE_DIR}/src/kernel/blas1/ucopy.asm
    ${PROJECT_SOURCE_DIR}/src/kernel/blas1/uswap.asm

)

set(INCLUDE_FILES
    ${BLAS_1_HEADERS}
)

set(SRC_FILES
    ${BLAS_1_SOURCES}
)

target_sources(nla.nla PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/includes FILES ${INCLUDE_FILES})
target_sources(nla.nla PRIVATE ${SRC_FILES})

target_compile_options(
    nla.nla
    INTERFACE -Wall -Wextra -Wpedantic -march=native -masm=intel -O3 -fPIC
)
target_link_libraries(nla.nla INTERFACE fmt::fmt)
set_target_properties(nla.nla PROPERTIES LINKER_LANGUAGE CXX)
