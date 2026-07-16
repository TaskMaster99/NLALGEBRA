# NLALGEBRA

## Introduction

The NLALGEBRA (Numerical Linear Algebra) library aim to reproduce level 1, 2 and 3 of BLAS subroutines likes CBLAS, Opti-Blas, etc ... I'm building this library just for training my skills in c++ and x86_64 assembly (using NASM synthax), in cache-optimization (using Goto-Blas paper). And i aim to use other technics to compute faster kernel, likes GPU acceleration (HIP), multiprocessing (OpenMPI) and multithreading(OpenMP).

As for now, i've done :
- [x] Level 1 subroutines $\mu$ kernel in x86_64 assembly
    - [x] sdot
    - [x] ddot
    - [x] saxpy
    - [x] daxpy 
    - [ ] sscal
    - [ ] dscal
    - [ ] sswap
    - [ ] dswap
    - [ ] scopy
    - [ ] dcopy
    - [ ] snorm1
    - [ ] dnorm1
    - [ ] snorm2
    - [ ] dnorm2
    - [ ] snorminf
    - [ ] dnorminf 
