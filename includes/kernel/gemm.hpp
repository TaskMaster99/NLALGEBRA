#pragma once

#include <utils.hpp>
#include <dot.hpp>
#include <axpy.hpp>

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