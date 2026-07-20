#include <utils.hpp>

/**
 * @brief Single-precision scaling vector micro kernel
 * @param salpha Single-precision constant
 * @param sx Single-precision scalar vector
 * @param sy Single-precision scalar vector
 * @param N  Size of the vectors
 */
extern "C" {void SSCAL(float salpha, const float* sx, float* sy, int N);}

/**
 * @brief Double-precision scaling vector micro kernel
 * @param dalpha Double-precision constant
 * @param dx Double-precision scalar vector
 * @param dy Double-precision scalar vector
 * @param N  Size of the vectors
 */
extern "C" {void DSCAL(double dalpha, const double* dx, double* dy, int N);}