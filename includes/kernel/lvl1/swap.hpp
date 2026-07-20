#include <utils.hpp>

/**
 * @brief Single-precision swapping micro kernel
 * @param sx Single-precision scalar vector
 * @param sy Single-precision scalar vector
 * @param N  Size of the vectors
 */
extern "C" {void SSWAP(float* sx, float* sy, int N);}

/**
 * @brief Double-precision swapping micro kernel
 * @param dx Double-precision scalar vector
 * @param dy Double-precision scalar vector
 * @param N  Size of the vectors
 */
extern "C" {void DSWAP(double* dx, double* dy, int N);}