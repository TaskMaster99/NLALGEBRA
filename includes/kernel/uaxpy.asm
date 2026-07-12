section .data
section .bss
section .text

global us_4_axpy
global us_8_axpy
global ud_4_axpy

us_4_axpy:
    vbroadcastss xmm0, [rdi] # a
    movups       xmm1, [rsi] # x
    movups       xmm2, [rdx] # y
    vfmadd132ss  xmm1,  xmm0, xmm2 # ax + y

saxpy:
    vbroadcastss xmm0, [rdi] # a
    movups       xmm1, [rsi] # x
    movups       xmm2, [rdx] # y
    vfmadd132ss  xmm1,  xmm0, xmm2 # ax + y

us_8_axpy:
    vbroadcastss ymm0, [rdi] # a
    vmovups      ymm1, [rsi] # x
    vmovups      ymm2, [rdx] # y
    vfmadd132ps  ymm1, ymm0, ymm2 # ax + y

ud_4_axpy:
    vbroadcastss ymm0, [rdi] # a
    vmovups      ymm1, [rsi] # x
    vmovups      ymm2, [rdx] # y
    vfmadd132ps  ymm1, ymm0, ymm2 # ax + y