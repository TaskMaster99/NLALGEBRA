#include <utils.hpp>


extern "C" 
{
    /**
     * @brief Single-precision swapping micro kernel
     * @param sx Single-precision scalar vector
     * @param sy Single-precision scalar vector
     * @param N  Size of the vectors
     */
    void x86__SSWAP__(float* sx, float* sy, int N);

    /**
     * @brief Double-precision swapping micro kernel
     * @param dx Double-precision scalar vector
     * @param dy Double-precision scalar vector
     * @param N  Size of the vectors
     */
    void x86__DSWAP__(double* dx, double* dy, int N);
}

void SSWAP(float* sx, int incx, float* sy, int incy, int N)
{
    if(incx == 1 && incy == 1)
    #ifdef __x86_64__
        x86__SSWAP__(sx, sy, N);
    #endif
    else
    {
        for(int i = 0; i < N; ++i)
            swap<float>(sx[incx * i], sy[incy * i]);
    }
}

void DSWAP(double* dx, int incx, double* dy, int incy, int N)
{
    if(incx == 1 && incy == 1)
    #ifdef __x86_64__
        x86__DSWAP__(dx, dy, N);
    #endif
    else
    {
        for(int i = 0; i < N; ++i)
            swap<double>(dx[incx * i], dy[incy * i]);
    }
}
