#pragma once

#include <utils.hpp>

/**
 * @brief Single-precision axpy constant times scalar vector plus scalar vector
 * @param salpha Single-precision constant
 * @param sx Single-precision scalar vector
 * @param sy Single-precision scalar vector
 * @param N  Size of the vectors
 *///                    xmm0          rdi           rsi      rdx
extern "C" {void SAXPY(float salpha, const float* sx, float* sy, int N);}


/**
 * @brief Double-precision axpy constant times scalar vector plus scalar vector
 * @param dalpha Double-precision constant
 * @param dx Double-precision scalar vector
 * @param dy Double-precision scalar vector
 * @param N  Size of the vectors
 *///                       ymm0            rdi          rsi      rdx
extern "C" {void DAXPY(double dalpha, const double* sx, double* sy, int N);}
