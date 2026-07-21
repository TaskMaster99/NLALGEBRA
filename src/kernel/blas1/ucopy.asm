section .data
section .bss
section .text

global x86__SCOPY__
global x86__DCOPY__

x86__SCOPY__:
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
    vmovups     ymm1, [rsi + rdx]
    vmovups     ymm2, [rsi + rdx + 0x20]
    vmovups     ymm3, [rsi + rdx + 0x40]
    vmovups     ymm4, [rsi + rdx + 0x60]

    vmovups     [rdi + rdx],        ymm1
    vmovups     [rdi + rdx + 0x20], ymm2
    vmovups     [rdi + rdx + 0x40], ymm3
    vmovups     [rdi + rdx + 0x60], ymm4

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
    vmovups     ymm5,         [rsi + rdx]
    vmovups     [rdi + rdx],  ymm5

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
    vmovups     xmm6,         [rsi + rdx]
    vmovups     [rdi + rdx],  xmm6

    add    rdx,  0x10
    cmp    rdx,  r8
    jb     SLOOP1
    cmp    rdx,  r9
    je     SEND

    STAIL:
    vmovss      xmm7,         [rsi + rdx]    
    vmovss      [rdi + rdx],  xmm7

    add    rdx,  0x04
    cmp    rdx,  r9
    jb     STAIL

    SEND:
    ret


x86__DCOPY__:
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
    vmovupd     ymm1, [rsi + rdx]
    vmovupd     ymm2, [rsi + rdx + 0x20]
    vmovupd     ymm3, [rsi + rdx + 0x40]
    vmovupd     ymm4, [rsi + rdx + 0x60]

    vmovupd      [rdi + rdx],        ymm1
    vmovupd      [rdi + rdx + 0x20], ymm2
    vmovupd      [rdi + rdx + 0x40], ymm3
    vmovupd      [rdi + rdx + 0x60], ymm4

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
    vmovupd     ymm5, [rsi + rdx]
    vmovupd     [rdi + rdx],  ymm5

    add    rdx,  0x20
    cmp    rdx,  rcx
    jb     DLOOP1
    cmp    rdx,  r8
    je     DEND

    DTAIL:
    vmovsd      xmm6, [rsi + rdx]    
    vmovsd      [rdi + rdx],  xmm6

    add    rdx,  0x08
    cmp    rdx,  r8
    jb     DTAIL

    DEND:
    ret
