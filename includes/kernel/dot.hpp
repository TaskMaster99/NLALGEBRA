#pragma once

#include <kernel/utils.hpp>


/**
 * @brief Single-precision 128bit dot product micro-kernel
 * @param sx Single-precision 128bit-vector
 * @param sy Single-precision 128bit-vector
 * @return Single-precision micro scalar result
 */
extern "C" {float us_4_dot(const float* sx, const float* sy);}

/**
 * @brief Single-precision 128bit dot product micro-kernel
 * @param sx Single-precision 128bit-vector
 * @param sy Single-precision 128bit-vector
 * @return Single-precision micro scalar result
 */
extern "C" {float _sdot(const float* sx, const float* sy, int n);}

/**
 * @brief Single-precision 128bit dot product micro-kernel
 * @param sx Single-precision 128bit-vector
 * @param sy Single-precision 128bit-vector
 * @return Single-precision micro scalar result
 */
extern "C" {float _unroll_sdot(const float* sx, const float* sy, int n);}


/**
 * @brief Single-precision 256bit dot product micro-kernel
 * @param sx Single-precision 256bit-vector
 * @param sy Single-precision 256bit-vector
 * @return Single-precision micro scalar result
 */
extern "C" {float us_8_dot(const float* sx, const float* sy);}


/**
 * @brief Double-precision 256bit dot product micro-kernel
 * @param sx Double-precision 256bit-vector
 * @param sy Double-precision 256bit-vector
 * @return Double-precision micro scalar result
 */
extern "C" {double ud_4_dot(const double* sx, const double* sy);}

/**
 * @brief Single-precision dot product kernel
 * @param sx Single-precision vector
 * @param sy Single-precision vector
 * @return Single-precision scalar result
 */
float sdot(const float* sx, const float* sy, int N)
{
    if(!sx)    return __FLT_NORM_MAX__;
    if(!sy)    return __FLT_NORM_MAX__;
    if(N <= 0) return __FLT_NORM_MAX__;
    
    float res = 0.0f;
    int i = 0;

    if(N >= COMPATIBLE_128BIT)
    {
        int pN = N/COMPATIBLE_128BIT;
        for(; i < pN; i += 4)
            res += us_4_dot(sx+i, sy+i);
    }
    else if(N >= COMPATIBLE_256BIT)
    {
        int pN = N/COMPATIBLE_256BIT;
        for(; i < pN; i += 8)
            res += us_8_dot(sx+i, sy+i);
    }

    for(; i < N; i += 1)
        res += sx(i) + sy(i);

    return res;
}


/**
 * @brief Double-precision dot product kernel
 * @param dx Double-precision scalar vector
 * @param dy Double-precision scalar vector
 * @return Double-precision scalar result
 */
float ddot(const double* dx, const double* dy, int N)
{
    if(!dx)    return __FLT_NORM_MAX__;
    if(!dy)    return __FLT_NORM_MAX__;
    if(N <= 0) return __FLT_NORM_MAX__;
    
    double res = 0.0f;
    int i = 0;

    if(N >= COMPATIBLE_256BIT)
    {
        int pN = N/COMPATIBLE_256BIT;
        for(; i < pN; i += 8)
            res += ud_4_dot(dx+i, dy+i);
    }

    for(; i < N; i += 1)
        res += dx(i) + dy(i);

    return res;
}