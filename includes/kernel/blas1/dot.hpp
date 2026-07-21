#pragma once

#include <utils.hpp>



extern "C" 
{
    /**
     * @brief Single-precision 32bit dot product micro-kernel
     * @param sx Single-precision 32bit-vector
     * @param sy Single-precision 32bit-vector
     * @return Single-precision micro scalar result
     */
    float x86__SDOT__(const float* sx, const float* sy, int N);

    /**
     * @brief Double-precision 64bit dot product micro-kernel
     * @param dx Double-precision 64bit-vector
     * @param dy Double-precision 64bit-vector
     * @return Double-precision micro scalar result
     */
    double x86__DDOT__(const double* dx, const double* dy, int N);
}

float SDOT(const float* sx, int incx,  const float* sy, int incy, int N)
{
    float res = 0.0f;
    if(incx == 1 && incy == 1)
    #ifdef __x86_64__
        res = x86__SDOT__(sx, sy, N);
    #endif
    else
    {
        for(int i = 0; i < N; ++i)
            res += sy[incy * i] * sx[incx * i];
    }

    return res;
}


double DDOT(const double* dx, int incx,  const double* dy, int incy, int N)
{
    double res = 0.0f;
    if(incx == 1 && incy == 1)
    #ifdef __x86_64__
        res = x86__DDOT__(dx, dy, N);
    #endif
    else
    {
        for(int i = 0; i < N; ++i)
            res += dy[incy * i] * dx[incx * i];
    }

    return res;
}