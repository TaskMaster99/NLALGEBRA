#pragma once

#include <utils.hpp>


extern "C" 
{
    /**
     * @brief Single-precision x86_64 assembly axpy subroutines
     * @param salpha Single-precision constant
     * @param sx Single-precision scalar vector
     * @param sy Single-precision scalar vector
     * @param N  Size of the vectors
    */
    void x86__SAXPY__(float salpha, const float* sx, float* sy, int N);

    /**
     * @brief Double-precision x86_64 assembly axpy subroutines
     * @param dalpha Double-precision constant
     * @param dx Double-precision scalar vector
     * @param dy Double-precision scalar vector
     * @param N  Size of the vectors
     */
    void x86__DAXPY__(double dalpha, const double* sx, double* sy, int N);
}



/**
 * @brief Single-precision axpy subroutines 
 * @param salpha Single-precision constant
 * @param sx Single-precision scalar vector
 * @param incx Increment step on sx
 * @param sy Single-precision scalar vector
 * @param incy Increment step on sy
 * @param N  Size of the vectors
**/
void SAXPY(float salpha, const float* sx,int incx, float* sy, int incy, int N)
{
    if(incx ==1 && incy == 1)
        #ifdef __x86_64__
            x86__SAXPY__(salpha, sx, sy, N);
        #endif
    else
    {
        for(int i = 0; i < N; ++i)
            sy[incy * i] = salpha*sx[incx * i] + sy[incy * i];
    }
}

/**
 * @brief Double-precision axpy subroutines 
 * @param dalpha Double-precision constant
 * @param dx Double-precision scalar vector
 * @param incx Increment step on sx
 * @param dy Double-precision scalar vector
 * @param incy Increment step on sy
 * @param N  Size of the vectors
**/
void DAXPY(double dalpha, const double* dx,int incx, double* dy, int incy, int N)
{
    if(incx ==1 && incy == 1)
        #ifdef __x86_64__
            x86__DAXPY__(dalpha, dx, dy, N);
        #endif
    else
    {
        for(int i = 0; i < N; ++i)
            dy[incy * i] = dalpha*dx[incx * i] + dy[incy * i];
    }
}