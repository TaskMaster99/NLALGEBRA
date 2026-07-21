#include <utils.hpp>


extern "C" 
{
    /**
     * @brief Single-precision scaling vector micro kernel
     * @param salpha Single-precision constant
     * @param sx Single-precision scalar vector
     * @param sy Single-precision scalar vector
     * @param N  Size of the vectors
     */
    void x86__SSCAL__(float salpha, const float* sx, float* sy, int N);


    /**
     * @brief Double-precision scaling vector micro kernel
     * @param dalpha Double-precision constant
     * @param dx Double-precision scalar vector
     * @param dy Double-precision scalar vector
     * @param N  Size of the vectors
     */
    void x86__DSCAL__(double dalpha, const double* dx, double* dy, int N);
}

void SSCAL(float salpha, const float* sx, int incx, float* sy, int incy, int N)
{
    if(incx == 1 && incy == 1)
    #ifdef __x86_64__
        x86__SSCAL__(salpha, sx, sy, N);
    #endif
    else
    {
        for(int i = 0; i < N; ++i)
            sy[incy * i] = salpha * sx[incx * i];
    }
}

void DSCAL(double dalpha, const double* dx, int incx, double* dy, int incy, int N)
{
    if(incx == 1 && incy == 1)
    #ifdef __x86_64__
        x86__DSCAL__(dalpha, dx, dy, N);
    #endif
    else
    {
        for(int i = 0; i < N; ++i)
            dy[incy * i] = dalpha * dx[incx * i];
    }
}