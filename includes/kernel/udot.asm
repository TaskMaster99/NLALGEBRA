section .data
section .bss
section .text

global SDOT
global DDOT

SDOT:
    vxorps  ymm2, ymm2
    vxorps  ymm3, ymm3
    vxorps  ymm4, ymm4
    vxorps  ymm5, ymm5
    vxorps  ymm6, ymm6

    vxorps  xmm7, xmm7
    vxorps  xmm8, xmm8

    test   rdx, rdx 
    jz     SEND
    mov    rax, rdx

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
    shl    r9,  0x02

    xor    rdx, rdx
    test   rax, rax
    jz     SCHECKING0

    SUNROLL_LOOP:
    vmovups     ymm0, [rdi + rdx]
    vmovups     ymm1, [rsi + rdx]
    vfmadd231ps ymm2, ymm0, ymm1

    vmovups     ymm0, [rdi + rdx + 0x20]
    vmovups     ymm1, [rsi + rdx + 0x20]
    vfmadd231ps ymm3, ymm0, ymm1

    vmovups     ymm0, [rdi + rdx + 0x40]
    vmovups     ymm1, [rsi + rdx + 0x40]
    vfmadd231ps ymm4, ymm0, ymm1

    vmovups     ymm0, [rdi + rdx + 0x60]
    vmovups     ymm1, [rsi + rdx + 0x60]
    vfmadd231ps ymm5, ymm0, ymm1


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
    vmovups     ymm0, [rdi + rdx]
    vmovups     ymm1, [rsi + rdx]
    vfmadd231ps ymm6, ymm0, ymm1
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
    vmovups xmm0, [rdi + rdx]
    vmovups xmm1, [rsi + rdx]
    vfmadd231ps xmm7, xmm0, xmm1

    add    rdx,  0x10
    cmp    rdx,  r8
    jb     SLOOP1
    cmp    rdx,  r9
    je     SEND

    STAIL:
    movss  xmm0, [rdi + rdx]
    movss  xmm1, [rsi + rdx]
    mulss  xmm0, xmm1
    addss  xmm8, xmm0

    add    rdx,  0x04
    cmp    rdx,  r9
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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;double precision dot product micro kernel;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

DDOT:
    vxorpd  ymm2, ymm2
    vxorpd  ymm3, ymm3
    vxorpd  ymm4, ymm4
    vxorpd  ymm5, ymm5

    vxorpd   xmm6, xmm6
    vxorpd   xmm7, xmm7


    test   rdx, rdx 
    jz     DEND
    mov    rax, rdx 

    mov    rcx, rax  ;63
    shr    rax, 0x04 ;63 >> 4 = 3
    shl    rax, 0x07 ;384
    and    rcx, 0x0F ;15

    shr    rcx, 0x02 ;15 >> 2 = 7
    shl    rcx, 0x04 ;112

    mov    r8, rdx
    shl    r8, 0x03

    xor    rdx, rdx
    test   rax, rax
    jz     DCHECKING0

    DUNROLL_LOOP:
    vmovupd     ymm0, [rdi + rdx]
    vmovupd     ymm1, [rsi + rdx]
    vfmadd231pd ymm2, ymm0, ymm1

    vmovupd     ymm0, [rdi + rdx + 0x20]
    vmovupd     ymm1, [rsi + rdx + 0x20]
    vfmadd231pd ymm3, ymm0, ymm1

    vmovupd     ymm0, [rdi + rdx + 0x40]
    vmovupd     ymm1, [rsi + rdx + 0x40]
    vfmadd231pd ymm4, ymm0, ymm1

    vmovupd     ymm0, [rdi + rdx + 0x60]
    vmovupd     ymm1, [rsi + rdx + 0x60]
    vfmadd231pd ymm5, ymm0, ymm1

    add    rdx, 0x80
    cmp    rdx, rax
    jb     DUNROLL_LOOP
    cmp    rdx, r8
    je     DEND

    DCHECKING0:
    test   rcx, rcx
    jz     DTAIL 

    add    rcx, rax

    DLOOP1:
    vmovupd xmm0, [rdi + rdx]
    vmovupd xmm1, [rsi + rdx]
    vfmadd231pd xmm6, xmm0, xmm1

    add    rdx,  0x10
    cmp    rdx,  rcx
    jb     DLOOP1
    cmp    rdx,  r8
    je     DEND

    DTAIL:
    movsd  xmm0, [rdi + rdx]
    movsd  xmm1, [rsi + rdx]
    mulsd  xmm0, xmm1
    addsd  xmm7, xmm0

    add    rdx,  0x08
    cmp    rdx,  r8
    jb     DTAIL

    DEND:
    vextractf128 xmm9, ymm2, 1     
    vaddpd       xmm2, xmm2, xmm9  
    vhaddpd      xmm2, xmm2, xmm2

    vextractf128 xmm9, ymm3, 1
    vaddpd       xmm3, xmm3, xmm9
    vhaddpd      xmm3, xmm3, xmm3

    vextractf128 xmm9, ymm4, 1
    vaddpd       xmm4, xmm4, xmm9
    vhaddpd      xmm4, xmm4, xmm4

    vextractf128 xmm9, ymm5, 1
    vaddpd       xmm5, xmm5, xmm9
    vhaddpd      xmm5, xmm5, xmm5

    vhaddpd      xmm6, xmm6, xmm6
    vhaddpd      xmm7, xmm7, xmm7

    vaddsd       xmm3, xmm2
    vaddsd       xmm4, xmm3
    vaddsd       xmm5, xmm4
    vaddsd       xmm6, xmm5
    vaddsd       xmm7, xmm6
    movsd        xmm0, xmm7
    ret