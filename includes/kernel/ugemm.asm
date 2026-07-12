section .data
section .bss
section .text

global u_4x4_sgemm

u_4x4_sgemm:
    mov rax,
    vbroadcastss xmm0, [rdi] # alpha
    vbroadcastss xmm3, [rdx] # beta
    vbroadcastss xmm1, [rsi] # A

    movups xmm2, [rcx] # B
    movups xmm4, [r8]  # C
    mulps  xmm1, xmm0 # A x alpha

    vfmadd132ss  xmm4,  xmm3, xmm0 # C x beta +   A x alpha

    vbroadcastss xmm0, [rdi + ] # alpha
    vbroadcastss xmm3, [rdx] # beta
    vbroadcastss xmm1, [rsi] # A

    movups xmm2, [rcx] # B
    movups xmm4, [r8]  # C
    mulps  xmm1, xmm0 # A x alpha

    vfmadd132ss  xmm4,  xmm3, xmm0 # C x beta +   A x alpha




    