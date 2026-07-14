section .data
section .bss
section .text

global SAXPY
global us_8_axpy
global ud_4_axpy


SAXPY:
    vbroadcastss ymm0, [rdi]
    vxorps  ymm1, ymm1
    vxorps  ymm2, ymm2
    vxorps  ymm3, ymm3
    vxorps  ymm4, ymm4
    vxorps  ymm5, ymm5
    vxorps  ymm6, ymm6

    vxorps  xmm7, xmm7
    vxorps  xmm8, xmm8

    test   rcx, rcx 
    jz     SEND
    mov    rax, rcx

    mov    r10, rax
    shr    rax, 0x05
    shl    rax, 0x07
    and    r10, 0x1F

    mov    r11, r10
    shr    r13, 0x03
    shl    r13, 0x05
    and    r11, 0x07
    
    shr    r11, 0x02
    shl    r11, 0x04

    mov    r12, rcx
    shl    r12, 0x02

    xor    r12, r12
    test   rax, rax
    jz     SCHECKING0

    SUNROLL_LOOP:
    vmovups     ymm1, [rsi + r12]
    vfmadd231ps ymm2, ymm0, ymm1

    vmovups     ymm3, [rsi + r12 + 0x20]
    vfmadd231ps ymm4, ymm0, ymm3

    vmovups     ymm5, [rsi + r12 + 0x40]
    vfmadd231ps ymm6, ymm0, ymm5

    vmovups     ymm7, [rsi + r12 + 0x60]
    vfmadd231ps ymm8, ymm0, ymm5

    movaps      [rdx + r12],        ymm2
    movaps      [rdx + r12 + 0x20], ymm4
    movaps      [rdx + r12 + 0x20], ymm6
    movaps      [rdx + r12 + 0x20], ymm8

    add    rdx, 0x80
    cmp    rdx, rax
    jb     SUNROLL_LOOP
    cmp    rdx, r10
    je     SEND

    SCHECKING0:
    test   rcx, rcx
    jz     SCHECKING1

    add    rcx,  rax

    SLOOP0:
    vmovups     ymm0, [rdi + rdx]
    vmovups     ymm1, [rsi + rdx]
    vfmadd231ps ymm6, ymm0, ymm1
    add    rdx, 0x20
    cmp    rdx, rcx
    jb     SLOOP0
    cmp    rdx, r10
    je     SEND

    SCHECKING1:
    test   r11, r11
    jz     STAIL 

    add    r11,  rcx

    SLOOP1:
    vmovups xmm0, [rdi + rdx]
    vmovups xmm1, [rsi + rdx]
    vfmadd231ps xmm7, xmm0, xmm1

    add    rdx,  0x10
    cmp    rdx,  r11
    jb     SLOOP1
    cmp    rdx,  r10
    je     SEND

    STAIL:
    movss  xmm0, [rdi + rdx]
    movss  xmm1, [rsi + rdx]
    mulss  xmm0, xmm1
    addss  xmm8, xmm0

    add    rdx,  0x04
    cmp    rdx,  r10
    jb     STAIL

    SEND:
    vextractf128 xmm9, ymm2, 1
    vaddps       xmm2, xmm2, xmm9
    vhaddps      xmm2, xmm2, xmm2
    vhaddps      xmm2, xmm2, xmm2

    vextractf128 xmm9, ymm3, 1
    vaddps       xmm3, xmm3, xmm9
    vhaddps      xmm3, xmm3, xmm3
    vhaddps      xmm3, xmm3, xmm3

    vextractf128 xmm9, ymm4, 1
    vaddps       xmm4, xmm4, xmm9
    vhaddps      xmm4, xmm4, xmm4
    vhaddps      xmm4, xmm4, xmm4

    vextractf128 xmm9, ymm5, 1
    vaddps       xmm5, xmm5, xmm9
    vhaddps      xmm5, xmm5, xmm5
    vhaddps      xmm5, xmm5, xmm5

    vextractf128 xmm9, ymm6, 1
    vaddps       xmm6, xmm6, xmm9
    vhaddps      xmm6, xmm6, xmm6
    vhaddps      xmm6, xmm6, xmm6

    vhaddps      xmm7, xmm7, xmm7
    vhaddps      xmm7, xmm7, xmm7

    vaddss       xmm3, xmm3, xmm2
    vaddss       xmm4, xmm4, xmm3
    vaddss       xmm5, xmm5, xmm4
    vaddss       xmm6, xmm6, xmm5
    vaddss       xmm7, xmm7, xmm6
    vaddss       xmm8, xmm8, xmm7
    movss        xmm0, xmm8
    ret

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