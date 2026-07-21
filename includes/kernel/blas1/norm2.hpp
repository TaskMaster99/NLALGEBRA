#include <utils.hpp>


extern "C" 
{
    /**
     * @brief Single-precision x86 asm norm2
     * @param sx Single-precision scalar vector
     * @param incx Increment step on sx
     * @param N  Size of the vectors
     * @return norm2
     */
    float x86__SNORM2__(const float* sx, int N);


    /**
     * @brief Double-precision x86 asm norm2
     * @param dx Double-precision scalar vector
     * @param incx Increment step on sx
     * @param N  Size of the vectors
     * @return norm2
     */
    float x86__DNORM2__(const double* dx, int N);


}

float SNORM2(const float* sx, int incx, int N)
{
    float res = 0.0f;
    if(incx == 1)
    #ifdef __x86_64__
        res = x86__SNORM2__(sx, N);
    #endif
    else
    {
        for(int i = 0; i < N; ++i)
            res += sx[incx*i]*sx[incx*i];
        res = std::sqrtf(res);
    }

    return res;
}

double DNORM2(const double* dx, int incx, int N)
{
    double res = 0.0;
    if(incx == 1)
    #ifdef __x86_64__
        res = x86__DNORM2__(dx, N);
    #endif
    else
    {
        for(int i = 0; i < N; ++i)
            res += dx[incx*i]*dx[incx*i];
        res = std::sqrt(res);
    }

    return res;
}