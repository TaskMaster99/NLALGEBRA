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

#define EPSILON64_LV1 1e-3
#define EPSILON64_LV2 1e-6
#define EPSILON64_LV3 1e-9
#define EPSILON64_LV4 1e-12
#define EPSILON64_LV5 1e-15
#define EPSILON64_LV6 1e-18

#define ASSERTM(exp, msg) assert(((void)msg, exp))

namespace NLA
{
    template<typename T>
    [[gnu::always_inline]] static inline void swap(T& a, T& b)
    {
        T c = a;
        a = b;
        b = c;
    }
}