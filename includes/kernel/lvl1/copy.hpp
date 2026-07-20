#include <utils.hpp>

/**
 * @brief Single-precision 32bit copy micro-kernel
 * @param sx Single-precision 32bit-vector
 * @param sy Single-precision 32bit-vector
 * @param N Size of sx
 */
extern "C" {void SCOPY(const float* sx, float* sy, int N);}

/**
 * @brief Double-precision 64bit copy micro-kernel
 * @param dx Double-precision 64bit-vector
 * @param dy Double-precision 64bit-vector
 * @param N Size of dx
 */
extern "C" {void DCOPY(const double* dx, double* dy, int N);}