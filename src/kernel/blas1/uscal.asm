section .data
section .bss
section .text

global x86__SSCAL__
global x86__DSCAL__

x86__SSCAL__:
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
    vmulps      ymm1, ymm0

    vmovups     ymm2, [rdi + rdx + 0x20]
    vmulps      ymm2, ymm0

    vmovups     ymm3, [rdi + rdx + 0x40]
    vmulps      ymm3, ymm0

    vmovups     ymm4, [rdi + rdx + 0x60]
    vmulps      ymm4, ymm0

    vmovups      [rsi + rdx],        ymm1
    vmovups      [rsi + rdx + 0x20], ymm2
    vmovups      [rsi + rdx + 0x40], ymm3
    vmovups      [rsi + rdx + 0x60], ymm4

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
    vmovups     ymm5,  [rdi + rdx]
    vmulps      ymm5, ymm0

    vmovups      [rsi + rdx],  ymm5

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
    vmovups     xmm6, [rdi + rdx]
    vmulps      xmm6, xmm0

    vmovups      [rsi + rdx],  xmm6

    add    rdx,  0x10
    cmp    rdx,  r8
    jb     SLOOP1
    cmp    rdx,  r9
    je     SEND

    STAIL:
    vmovss      xmm7, [rdi + rdx]
    vmulss      xmm7, xmm0
    
    vmovss      [rsi + rdx],  xmm7

    add    rdx,  0x04
    cmp    rdx,  r9
    jb     STAIL

    SEND:
    ret


x86__DSCAL__:
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
    vmulpd      ymm1, ymm0

    vmovupd     ymm2, [rdi + rdx + 0x20]
    vmulpd      ymm2, ymm0

    vmovupd     ymm3, [rdi + rdx + 0x40]
    vmulpd      ymm3, ymm0

    vmovupd     ymm4, [rdi + rdx + 0x60]
    vmulpd      ymm4, ymm0

    vmovupd      [rsi + rdx],        ymm1
    vmovupd      [rsi + rdx + 0x20], ymm2
    vmovupd      [rsi + rdx + 0x40], ymm3
    vmovupd      [rsi + rdx + 0x60], ymm4

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
    vmovupd     xmm5, [rdi + rdx]
    vmulpd      xmm5, xmm0

    vmovupd      [rsi + rdx],  xmm5

    add    rdx,  0x10
    cmp    rdx,  rcx
    jb     DLOOP1
    cmp    rdx,  r8
    je     DEND

    DTAIL:
    vmovsd      xmm6, [rdi + rdx]
    vmulsd      xmm6, xmm0
    
    vmovsd      [rsi + rdx],  xmm6

    add    rdx,  0x08
    cmp    rdx,  r8
    jb     DTAIL

    DEND:
    ret