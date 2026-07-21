#include <utils.hpp>


extern "C" 
{
    /**
     * @brief Single-precision x86_64 assembly copy subroutines
     * @param sx Single-precision vector
     * @param sy Single-precision vector
     * @param N Size of sx
     */
    void x86__SCOPY__(const float* sx, float* sy, int N);


    /**
     * @brief Double-precision x86_64 assembly copy subroutines
     * @param dx Double-precision vector
     * @param dy Double-precision vector
     * @param N Size of dx
     */
    void x86__DCOPY__(const double* dx, double* dy, int N);
}



void SCOPY(const float* sx, int incx, float* sy, int incy, int N)
{
    if(incx == 1 && incy == 1)
    #ifdef __x86_64__
        x86__SCOPY__(sx, sy, N);
    #endif
    else
    {
        for(int i = 0; i < N; ++i)
            sy[incy * i] = sx[incx * i];
    }
}

void DCOPY(const double* dx, int incx, double* dy, int incy, int N)
{
    if(incx == 1 && incy == 1)
    #ifdef __x86_64__
        x86__DCOPY__(dx, dy, N);
    #endif
    else
    {
        for(int i = 0; i < N; ++i)
            dy[incy * i] = dx[incx * i];
    }
}