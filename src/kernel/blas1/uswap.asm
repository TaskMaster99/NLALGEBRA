section .data
section .bss
section .text

global x86__SSWAP__
global x86__DSWAP__


x86__SSWAP__:
    test   edx, edx 
    jz     SEND
    mov    eax, edx

    mov    rcx, rax
    shr    rax, 0x05
    shl    rax, 0x07
    and    rcx, 0x1F

    mov    r8, rcx
    shr    rcx, 0x03
    shl    rcx, 0x05
    and    r8, 0x07
    
    shr    r8, 0x02
    shl    r8, 0x04

    mov    r9, rdx
    shl    r9, 0x02

    xor    rdx, rdx
    test   rax, rax
    jz     SCHECKING0

    SUNROLL_LOOP:
    vmovups     ymm0, [rdi + rdx]
    vmovups     ymm1, [rsi + rdx]
    vmovups     [rdi + rdx], ymm1
    vmovups     [rsi + rdx], ymm0
    
    vmovups     ymm2, [rdi + rdx + 0x20]
    vmovups     ymm3, [rsi + rdx + 0x20]
    vmovups     [rdi + rdx + 0x20], ymm3
    vmovups     [rsi + rdx + 0x20], ymm2

    vmovups     ymm4, [rdi + rdx + 0x40]
    vmovups     ymm5, [rsi + rdx + 0x40]
    vmovups     [rdi + rdx + 0x40], ymm5
    vmovups     [rsi + rdx + 0x40], ymm4

    vmovups     ymm6, [rdi + rdx + 0x60]
    vmovups     ymm7, [rsi + rdx + 0x60]
    vmovups     [rdi + rdx + 0x60], ymm7
    vmovups     [rsi + rdx + 0x60], ymm6

    add    rdx, 0x80
    cmp    rdx, rax
    jb     SUNROLL_LOOP
    cmp    rdx, r9
    je     SEND

    SCHECKING0:
    test   rcx, rcx
    jz     SCHECKING1

    add    rcx,  rax

    SLOOP0:
    vmovups     ymm8, [rdi + rdx]
    vmovups     ymm9, [rsi + rdx]
    vmovups     [rdi + rdx], ymm9
    vmovups     [rsi + rdx], ymm8

    add    rdx, 0x20
    cmp    rdx, rcx
    jb     SLOOP0
    cmp    rdx, r9
    je     SEND

    SCHECKING1:
    test   r8, r8
    jz     STAIL 

    add    r8,  rcx

    SLOOP1:

    vmovups     xmm10, [rdi + rdx]
    vmovups     xmm11, [rsi + rdx]
    vmovups     [rdi + rdx], xmm11
    vmovups     [rsi + rdx], xmm10

    add    rdx,  0x10
    cmp    rdx,  r8
    jb     SLOOP1
    cmp    rdx,  r9
    je     SEND

    STAIL:
    vmovss     xmm12, [rdi + rdx]
    vmovss     xmm13, [rsi + rdx]
    vmovss     [rdi + rdx], xmm13
    vmovss     [rsi + rdx], xmm12

    add    rdx,  0x04
    cmp    rdx,  r9
    jb     STAIL

    SEND:
    ret


x86__DSWAP__:
    test   edx, edx 
    jz     DEND
    mov    eax, edx

    mov    rcx, rax
    shr    rax, 0x04
    shl    rax, 0x07
    and    rcx, 0x0F

    shr    rcx, 0x02
    shl    rcx, 0x04

    mov    r8, rdx
    shl    r8, 0x03

    xor    rdx, rdx
    test   rax, rax
    jz     DCHECKING0

    DUNROLL_LOOP:
    vmovupd     ymm0, [rdi + rdx]
    vmovupd     ymm1, [rsi + rdx]
    vmovupd     [rdi + rdx], ymm1
    vmovupd     [rsi + rdx], ymm0
    
    vmovupd     ymm2, [rdi + rdx + 0x20]
    vmovupd     ymm3, [rsi + rdx + 0x20]
    vmovupd     [rdi + rdx + 0x20], ymm3
    vmovupd     [rsi + rdx + 0x20], ymm2

    vmovupd     ymm4, [rdi + rdx + 0x40]
    vmovupd     ymm5, [rsi + rdx + 0x40]
    vmovupd     [rdi + rdx + 0x40], ymm5
    vmovupd     [rsi + rdx + 0x40], ymm4

    vmovupd     ymm6, [rdi + rdx + 0x60]
    vmovupd     ymm7, [rsi + rdx + 0x60]
    vmovupd     [rdi + rdx + 0x60], ymm7
    vmovupd     [rsi + rdx + 0x60], ymm6

    add    rdx, 0x80
    cmp    rdx, rax
    jb     DUNROLL_LOOP
    cmp    rdx, r8
    je     DEND

    DCHECKING0:
    test   rcx, rcx
    jz     DTAIL

    add    rcx,  rax

    DLOOP1:
    vmovupd     ymm8, [rdi + rdx]
    vmovupd     ymm9, [rsi + rdx]
    vmovupd     [rdi + rdx], ymm9
    vmovupd     [rsi + rdx], ymm8

    add    rdx,  0x20
    cmp    rdx,  rcx
    jb     DLOOP1
    cmp    rdx,  r8
    je     DEND

    DTAIL:
    vmovsd     xmm10, [rdi + rdx]
    vmovsd     xmm11, [rsi + rdx]
    vmovsd     [rdi + rdx], xmm11
    vmovsd     [rsi + rdx], xmm10

    add    rdx,  0x08
    cmp    rdx,  r8
    jb     DTAIL

    DEND:
    ret
