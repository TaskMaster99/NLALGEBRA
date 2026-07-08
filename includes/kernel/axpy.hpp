#pragma once

#include <utils.hpp>

/**
 * @brief Single-precision axpy constant times scalar vector plus scalar vector
 * @param sa Single-precision constant
 * @param sx Single-precision scalar vector
 * @param sy Single-precision scalar vector
 * @param N  Size of the vectors
 */
void saxpy(float sa, const float* sx, float* sy, int N)
{
    if(!sa)    return;
    if(!sx)    return;
    if(!sy)    return;
    if(N <= 0) return;
    
    int n      = N % 4;
    int offset = !n ? 4 : 1;
    int i      = 0;

    if(!n)
    {
        do
        {
            sy(i)   =  sy(i)   + sa*sx(i);
            sy(i+1) =  sy(i+1) + sa*sx(i+1);
            sy(i+2) =  sy(i+2) + sa*sx(i+2);
            sy(i+3) =  sy(i+3) + sa*sx(i+3);
            i      += offset;
        }while(i < N);
    }
    else
    {
        do
        {
            sy(i)   =  sy(i)   + sa*sx(i);
            i++;
        }while(i < N);
    }

}

/**
 * @brief Double-precision axpy constant times scalar vector plus scalar vector
 * @param da Double-precision constant 
 * @param dx Double-precision scalar vector
 * @param dy Double-precision scalar vector
 * @param N  Size of the vectors
 */
void daxpy(double da, const double* dx, double* dy, int N)
{
    if(!da)    return;
    if(!dx)    return;
    if(!dy)    return;
    if(N <= 0) return;
    
    int n      = N % 4;
    int offset = !n ? 4 : 1;
    int i      = 0;

    if(!n)
    {
        do
        {
            dy(i)   =  dy(i)   + da  * dx(i);
            dy(i+1) =  dy(i+1) + da  * dx(i+1);
            dy(i+2) =  dy(i+2) + da  * dx(i+2);
            dy(i+3) =  dy(i+3) + da  * dx(i+3);
            i      += offset;
        }while(i < N);
    }
    else
    {
        do
        {
            dy(i)   =  dy(i)   + da  *dx(i);
            i++;
        }while(i < N);
    }

}



/**
 * @brief Single-precision axpby constant times vector plus constant times vector
 * @param sa Single-precision constant
 * @param sx Single-precision scalar vector
 * @param sb Single-precision constant
 * @param sy Single-precision scalar vector
 * @param N  Size of the vectors
 */
void saxpby(float sa, const float* sx, float sb, float* sy, int N)
{
    if(!sa)    return;
    if(!sx)    return;
    if(!sy)    return;
    if(N <= 0) return;
    
    int n      = N % 4;
    int offset = !n ? 4 : 1;
    int i      = 0;

    if(!n)
    {
        do
        {
            sy(i)   =  sb * sy(i)   + sa*sx(i);
            sy(i+1) =  sb * sy(i+1) + sa*sx(i+1);
            sy(i+2) =  sb * sy(i+2) + sa*sx(i+2);
            sy(i+3) =  sb * sy(i+3) + sa*sx(i+3);
            i      += offset;
        }while(i < N);
    }
    else
    {
        do
        {
            sy(i)   =  sb * sy(i)   + sa*sx(i);
            i++;
        }while(i < N);
    }

}


/**
 * @brief Double-precision axpby constant times vector plus constant times vector
 * @param da Double-precision constant
 * @param dx Double-precision scalar vector
 * @param db Double-precision constant
 * @param dy Double-precision scalar vector
 * @param N  Size of the vectors
 */
void daxpby(double da, const double* dx, double db, double* dy, int N)
{
    if(!da)    return;
    if(!dx)    return;
    if(!dy)    return;
    if(N <= 0) return;
    
    int n      = N % 4;
    int offset = !n ? 4 : 1;
    int i      = 0;

    if(!n)
    {
        do
        {
            dy(i)   =  db * dy(i)   + da*dx(i);
            dy(i+1) =  db * dy(i+1) + da*dx(i+1);
            dy(i+2) =  db * dy(i+2) + da*dx(i+2);
            dy(i+3) =  db * dy(i+3) + da*dx(i+3);
            i      += offset;
        }while(i < N);
    }
    else
    {
        do
        {
            dy(i)   =  db * dy(i)   + da*dx(i);
            i++;
        }while(i < N);
    }

}