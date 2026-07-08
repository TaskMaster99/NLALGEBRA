#pragma once

#include <utils.hpp>

/**
 * @brief Single-precision scalar dot product
 * @param sx Single-precision scalar vector
 * @param sy Single-precision scalar vector
 * @return Single-precision scalar result
 */
float sdot(const float* sx, const float* sy, int N)
{
    if(!sx)    return __FLT_NORM_MAX__;
    if(!sy)    return __FLT_NORM_MAX__;
    if(N <= 0) return __FLT_NORM_MAX__;
    
    int n      = N % 4;
    int offset = !n ? 4 : 1;
    int i      = 0;

    float res = 0.0f;
    if(!n)
    {
        do
        {
            res +=  sx(i)  *sy(i);
            res +=  sx(i+1)*sy(i+1);
            res +=  sx(i+2)*sy(i+2);
            res +=  sx(i+3)*sy(i+3);
            i      += offset;
        }while(i < N);
    }
    else
    {
        do
        {
            res +=  sx(i)  *sy(i);
            i++;
        }while(i < N);
    }

    return res;
}


/**
 * @brief Double-precision scalar dot product
 * @param dx Double-precision scalar vector
 * @param dy Double-precision scalar vector
 * @return Double-precision scalar result
 */
float sdot(const float* dx, const float* dy, int N)
{
    if(!dx)    return __FLT_NORM_MAX__;
    if(!dy)    return __FLT_NORM_MAX__;
    if(N <= 0) return __FLT_NORM_MAX__;
    
    int n      =  N % 4;
    int offset = !n ? 4 : 1;
    int i      =  0;

    float res  =  0.0f;
    if(!n)
    {
        do
        {
            res +=  dx(i)  *dy(i);
            res +=  dx(i+1)*dy(i+1);
            res +=  dx(i+2)*dy(i+2);
            res +=  dx(i+3)*dy(i+3);
            i      += offset;
        }while(i < N);
    }
    else
    {
        do
        {
            res +=  dx(i)  *dy(i);
            i++;
        }while(i < N);
    }

    return res;
}