#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <kernel/lvl1/dot.hpp>
#include <kernel/lvl1/axpy.hpp>

using namespace Catch::Matchers;

TEST_CASE("micro kernel ", "[SDOT]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const float min = -10.0f;
    const float max =  10.0f;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_real_distribution<float> dist_numbers(min, max);

    float a[n] ;
    float b[n] ;

    for(int i = 0; i < N; ++i)
    {
        const int size = dist_size(rd);

        for(int j = 0; j < n; ++j)
        {
            a[j] = dist_numbers(rd);
            b[j] = dist_numbers(rd);
        }

        float real_res = 0.0f;

        for(int k = 0; k < size; ++k)
            real_res = std::fma(a[k], b[k], real_res);

        REQUIRE_THAT(SDOT(a,b, size), WithinRel(real_res, 1e-3f));
    }
}

TEST_CASE("micro kernel ", "[DDOT]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const double min = -10000.0;
    const double max =  10000.0;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_real_distribution<double> dist_numbers(min, max);

    double a[n] ;
    double b[n] ;

    for(int i = 0; i < N; ++i)
    {
        const int size = dist_size(rd);

        for(int j = 0; j < n; ++j)
        {
            a[j] = dist_numbers(rd);
            b[j] = dist_numbers(rd);
        }

        double real_res = 0.0;

        for(int k = 0; k < size; ++k)
            real_res = std::fma(a[k], b[k], real_res);

        REQUIRE_THAT(DDOT(a,b, size), WithinRel(real_res, 1e-3));
    }
}


TEST_CASE("micro kernel ", "[SAXPY]")
{
    const int N = 100;
    const int p = 10;
    const int n = 100;

    const float min = -10.0f;
    const float max =  10.0f;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_real_distribution<float> dist_numbers(min, max);

    float x[n] ;
    float y[n] ;
    float real_res_y[n] ;

    for(int i = 0; i < N; ++i)
    {
        const int   size  = dist_size(rd);
        const float alpha = dist_numbers(rd);

        for(int j = 0; j < n; ++j)
        {
            x[j] = dist_numbers(rd);
            y[j] = dist_numbers(rd);
            real_res_y[j] = y[j];
        }

        for(int k = 0; k < size; ++k)
            real_res_y[k] = std::fma(alpha, x[k], y[k]);

        SAXPY(alpha, x, y, size);

        for(int k = 0; k < size; ++k)
            REQUIRE_THAT(y[k], WithinRel(real_res_y[k], 1e-3f));
    }
}



TEST_CASE("micro kernel ", "[DAXPY]")
{
    const int N = 100;
    const int p = 10;
    const int n = 100;

    const double min = -10.0;
    const double max =  10.0;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_real_distribution<double> dist_numbers(min, max);

    double x[n] ;
    double y[n] ;
    double real_res_y[n] ;

    for(int i = 0; i < N; ++i)
    {
        const int   size  = dist_size(rd);
        const double alpha = dist_numbers(rd);

        for(int j = 0; j < n; ++j)
        {
            x[j] = dist_numbers(rd);
            y[j] = dist_numbers(rd);
            real_res_y[j] = y[j];
        }

        for(int k = 0; k < size; ++k)
            real_res_y[k] = std::fma(alpha, x[k], y[k]);

        DAXPY(alpha, x, y, size);

        for(int k = 0; k < size; ++k)
            REQUIRE_THAT(y[k], WithinRel(real_res_y[k], 1e-3));
    }
}