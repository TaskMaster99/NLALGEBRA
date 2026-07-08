#pragma once

#include <utils.hpp>
#include <dot.hpp>
#include <axpy.hpp>

/**
 * @brief Single-precision General Matrix Multiplication with column major matrices
 * @param salpha Single-precision scalar
 * @param sA Single-precision matrix left input
 * @param sB Single-precision matrix right input
 * @param sbeta Single-precision matrix result
 * @param sC Single-precision matrix result
 * @param M A row numbers and C row numbers
 * @param N B column numbers and C column numbers
 * @param P A column numbers and B row numbers
 */
void sgemm(float salpha, const float* sA, const float* sB, float sbeta, float* sC, int M, int N, int P)
{
    if(M == 0) return;
    if(N == 0) return;
    if(P == 0) return;

    if(!sA) return;
    if(!sB) return;
    if(!sC) return;

    int i      = 0;

    int j = 0;
    do
    {
        int k = 0;
        do
        {
            saxpby(salpha*sB(k,j), &sA(0,k), sbeta, &sC(0,j), M);
        }while(k++ < P);

    }while(j++ < N);
}

/**
 * @brief Double-precision General Matrix Multiplication with column major matrices
 * @param salpha Double-precision scalar
 * @param sA Double-precision matrix left input
 * @param sB Double-precision matrix right input
 * @param sbeta Double-precision matrix result
 * @param sC Double-precision matrix result
 * @param M A row numbers and C row numbers
 * @param N B column numbers and C column numbers
 * @param P A column numbers and B row numbers
 */
void dgemm(double dalpha, const double* dA, const double* dB, double dbeta, double* dC, int M, int N, int P)
{
    if(M == 0) return;
    if(N == 0) return;
    if(P == 0) return;

    if(!dA) return;
    if(!dB) return;
    if(!dC) return;

    int i      = 0;

    int j = 0;
    do
    {
        int k = 0;
        do
        {
            daxpby(dalpha*dB(k,j), &dA(0,k), dbeta, &dC(0,j), M);
        }while(k++ < P);

    }while(j++ < N);
}