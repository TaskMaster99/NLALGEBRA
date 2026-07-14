#pragma once

#include <kernel/utils.hpp>


/**
 * @brief Single-precision 32bit dot product micro-kernel
 * @param sx Single-precision 32bit-vector
 * @param sy Single-precision 32bit-vector
 * @return Single-precision micro scalar result
 */
extern "C" {float SDOT(const float* sx, const float* sy, int n);}

/**
 * @brief Double-precision 64bit dot product micro-kernel
 * @param dx Double-precision 64bit-vector
 * @param dy Double-precision 64bit-vector
 * @return Double-precision micro scalar result
 */
extern "C" {double DDOT(const double* dx, const double* dy, int n);}
