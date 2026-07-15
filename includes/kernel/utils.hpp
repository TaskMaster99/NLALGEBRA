#pragma once 

#include <cassert>
#include <fmt/core.h>
#include <random>

#define EPSILON32_LV0 1e-1f
#define EPSILON32_LV1 1e-3f
#define EPSILON32_LV2 1e-6f
#define EPSILON32_LV3 1e-9f
#define EPSILON32_LV4 1e-12f
#define EPSILON32_LV5 1e-15f
#define EPSILON32_LV6 1e-18f

#define EPSILON64_LV0 1e-1
#define EPSILON64_LV1 1e-3
#define EPSILON64_LV2 1e-6
#define EPSILON64_LV3 1e-9
#define EPSILON64_LV4 1e-12
#define EPSILON64_LV5 1e-15
#define EPSILON64_LV6 1e-18

#define ASSERTM(exp, msg) assert(((void)msg, exp))


#define sa(i) sa[i]
#define sx(i) sx[i]
#define sy(i) sy[i]

#define da(i) da[i]
#define dx(i) dx[i]
#define dy(i) dy[i]

#define sA(i,j) sA[j * P + i]
#define sB(i,j) sB[j * N + i]
#define sC(i,j) sC[j * N + i]

#define dA(i,j) dA[j * P + i]
#define dB(i,j) dB[j * N + i]
#define dC(i,j) dC[j * N + i]

#define COMPATIBLE_128BIT 4
#define COMPATIBLE_256BIT 8
