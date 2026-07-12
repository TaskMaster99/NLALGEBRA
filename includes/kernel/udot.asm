section .data
section .bss
section .text

global us_8_dot
global ud_4_dot
global _sdot
global _unroll_sdot


_sdot:
    xorps  xmm2, xmm2
    test   rdx, rdx
    jz     end
    mov    rax, rdx
    mov    rcx, rax
    shr    rax, 2
    shl    rax, 4
    shl    rcx, 2
    xor    rdx, rdx
    test   rax, rax
    jz     tail

    loop: 
    movups xmm0,[rdi + rdx]
    movups xmm1,[rsi + rdx]
    mulps  xmm0, xmm1
    addps  xmm2, xmm0
    add    rdx, 16
    cmp    rdx, rax
    jb     loop
    cmp    rdx, rcx
    je     end

    tail:
    movss  xmm0,[rdi + rdx]
    movss  xmm1,[rsi + rdx]
    mulss  xmm0, xmm1
    addss  xmm2, xmm0
    add    rdx, 4
    cmp    rdx, rcx
    jb     tail 

    end:
    haddps xmm2, xmm2
    haddps xmm2, xmm2
    movss  xmm0, xmm2
    ret



_unroll_sdot:
    xorps  xmm2, xmm2
    test   rdx, rdx 
    jz     end0
    mov    rax, rdx
    mov    rcx, rax
    shr    rax, 0x04
    shl    rax, 0x06
    and    rcx, 0x0F
    mov    rbx,  rcx
    shr    rcx, 0x02
    shl    rcx, 0x04
    shl    rbx,  0x02

    xor    rdx, rdx
    test   rax, rax
    jz     checking

    unroll_loop4: 
    movups xmm0,[rdi + rdx]
    movups xmm1,[rsi + rdx]
    mulps  xmm0, xmm1
    addps  xmm2, xmm0

    movups xmm0,[rdi + rdx + 16]
    movups xmm1,[rsi + rdx + 16]
    mulps  xmm0, xmm1
    addps  xmm2, xmm0

    movups xmm0,[rdi + rdx + 32]
    movups xmm1,[rsi + rdx + 32]
    mulps  xmm0, xmm1
    addps  xmm2, xmm0

    movups xmm0,[rdi + rdx + 48]
    movups xmm1,[rsi + rdx + 48]
    mulps  xmm0, xmm1
    addps  xmm2, xmm0

    add    rdx, 0x40
    cmp    rdx, rax
    jb     unroll_loop4
    cmp    rdx, rcx
    je     end0

    checking:
    test   rcx, rcx
    jz     tail1 

    loop1: 
    movups xmm0,[rdi + rdx]
    movups xmm1,[rsi + rdx]
    mulps  xmm0, xmm1
    addps  xmm2, xmm0
    add    rdx, 0x10
    cmp    rdx, rcx
    jb     loop
    cmp    rdx, rbx
    je     end0

    tail1:
    movss  xmm0,[rdi + rdx]
    movss  xmm1,[rsi + rdx]
    mulss  xmm0, xmm1
    addss  xmm2, xmm0
    add    rdx, 0x04
    cmp    rdx, rbx
    jb     tail1

    end0:
    haddps xmm2, xmm2
    haddps xmm2, xmm2
    movss  xmm0, xmm2
    ret

us_4_dot:
    movups xmm0,[rdi]
    movups xmm1,[rsi]
    mulps  xmm0, xmm1
    haddps xmm0, xmm0
    haddps xmm0, xmm0
    ret

us_8_dot:
    vmovups ymm0,[rdi]
    vmovups ymm1,[rsi]
    vmulps  ymm0, ymm1
    vhaddps ymm0, ymm0
    vhaddps ymm0, ymm0
    ret

ud_4_dot:
    vmovups ymm0,[rdi]
    vmovups ymm1,[rsi]
    vmulps  ymm0, ymm1
    vhaddps ymm0, ymm0
    vhaddps ymm0, ymm0
    ret