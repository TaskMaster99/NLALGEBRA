section .data
section .bss
section .text

global x86__SAXPY__
global x86__DAXPY__

x86__SAXPY__:
    vbroadcastss ymm0, xmm0

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
    vmovups     ymm1, [rdi + rdx]
    vmovups     ymm2, [rsi + rdx]
    vfmadd231ps ymm2, ymm0, ymm1

    vmovups     ymm3, [rdi + rdx + 0x20]
    vmovups     ymm4, [rsi + rdx + 0x20]
    vfmadd231ps ymm4, ymm0, ymm3

    vmovups     ymm5, [rdi + rdx + 0x40]
    vmovups     ymm6, [rsi + rdx + 0x40]
    vfmadd231ps ymm6, ymm0, ymm5

    vmovups     ymm7, [rdi + rdx + 0x60]
    vmovups     ymm8, [rsi + rdx + 0x60]
    vfmadd231ps ymm8, ymm0, ymm7

    vmovups      [rsi + rdx],        ymm2
    vmovups      [rsi + rdx + 0x20], ymm4
    vmovups      [rsi + rdx + 0x40], ymm6
    vmovups      [rsi + rdx + 0x60], ymm8

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
    vmovups     ymm9,  [rdi + rdx]
    vmovups     ymm10, [rsi + rdx]
    vfmadd231ps ymm10, ymm0, ymm9

    vmovups      [rsi + rdx],  ymm10

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
    vmovups     xmm11, [rdi + rdx]
    vmovups     xmm12, [rsi + rdx]
    vfmadd231ps xmm12, xmm0, xmm11

    vmovups      [rsi + rdx],  xmm12

    add    rdx,  0x10
    cmp    rdx,  r8
    jb     SLOOP1
    cmp    rdx,  r9
    je     SEND

    STAIL:
    vmovss      xmm13, [rdi + rdx]
    vmovss      xmm14, [rsi + rdx]
    vfmadd231ss xmm14, xmm0, xmm13
    
    vmovss      [rsi + rdx],  xmm14

    add    rdx,  0x04
    cmp    rdx,  r9
    jb     STAIL

    SEND:
    ret


x86__DAXPY__:
    vbroadcastsd ymm0, xmm0

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
    vmovupd     ymm1, [rdi + rdx]
    vmovupd     ymm2, [rsi + rdx]
    vfmadd231pd ymm2, ymm0, ymm1

    vmovupd     ymm3, [rdi + rdx + 0x20]
    vmovupd     ymm4, [rsi + rdx + 0x20]
    vfmadd231pd ymm4, ymm0, ymm3

    vmovupd     ymm5, [rdi + rdx + 0x40]
    vmovupd     ymm6, [rsi + rdx + 0x40]
    vfmadd231pd ymm6, ymm0, ymm5

    vmovupd     ymm7, [rdi + rdx + 0x60]
    vmovupd     ymm8, [rsi + rdx + 0x60]
    vfmadd231pd ymm8, ymm0, ymm7

    vmovupd      [rsi + rdx],        ymm2
    vmovupd      [rsi + rdx + 0x20], ymm4
    vmovupd      [rsi + rdx + 0x40], ymm6
    vmovupd      [rsi + rdx + 0x60], ymm8

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
    vmovupd     xmm11, [rdi + rdx]
    vmovupd     xmm12, [rsi + rdx]
    vfmadd231pd xmm12, xmm0, xmm11

    vmovupd      [rsi + rdx],  xmm12

    add    rdx,  0x10
    cmp    rdx,  rcx
    jb     DLOOP1
    cmp    rdx,  r8
    je     DEND

    DTAIL:
    vmovsd      xmm13, [rdi + rdx]
    vmovsd      xmm14, [rsi + rdx]
    vfmadd231sd xmm14, xmm0, xmm13
    
    vmovsd      [rsi + rdx],  xmm14

    add    rdx,  0x08
    cmp    rdx,  r8
    jb     DTAIL

    DEND:
    ret