#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <kernel/blas1/dot.hpp>
#include <kernel/blas1/axpy.hpp>
#include <kernel/blas1/copy.hpp>
#include <kernel/blas1/scal.hpp>
#include <kernel/blas1/swap.hpp>

#define MAX_SIZE 200

using namespace Catch::Matchers;

TEST_CASE("SDOT", "[BLAS 1]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const float min = -10.0f;
    const float max =  10.0f;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_int_distribution<int> dist_inc(1, 9);

    std::uniform_real_distribution<float> dist_numbers(min, max);

    float a[MAX_SIZE] ;
    float b[MAX_SIZE] ;

    for(int i = 0; i < N; ++i)
    {
        const int size = dist_size(rd);
        const int incx = dist_inc(rd);
        const int incy = dist_inc(rd);

        for(int j = 0; j < MAX_SIZE; ++j)
        {
            a[j] = dist_numbers(rd);
            b[j] = dist_numbers(rd);
        }

        float real_res = 0.0f;

        for(int k = 0; k < size; ++k)
            real_res = std::fma(a[k*incx], b[k*incy], real_res);

        REQUIRE_THAT(SDOT(a,incx,b,incy, size), WithinRel(real_res, 1e-3f));
    }
}

TEST_CASE("DDOT", "[BLAS 1]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const double min = -10000.0;
    const double max =  10000.0;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_int_distribution<int> dist_inc(1, 9);

    std::uniform_real_distribution<double> dist_numbers(min, max);

    double a[MAX_SIZE] ;
    double b[MAX_SIZE] ;

    for(int i = 0; i < N; ++i)
    {
        const int size = dist_size(rd);
        const int incx = dist_inc(rd);
        const int incy = dist_inc(rd);

        for(int j = 0; j < MAX_SIZE; ++j)
        {
            a[j] = dist_numbers(rd);
            b[j] = dist_numbers(rd);
        }

        double real_res = 0.0;

        for(int k = 0; k < size; ++k)
            real_res = std::fma(a[k*incx], b[k*incy], real_res);

        REQUIRE_THAT(DDOT(a,incx,b,incy, size), WithinRel(real_res, 1e-3));
    }
}


TEST_CASE("SAXPY", "[BLAS 1]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const float min = -10.0f;
    const float max =  10.0f;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_int_distribution<int> dist_inc(1, 9);

    std::uniform_real_distribution<float> dist_numbers(min, max);

    float x[MAX_SIZE] ;
    float y[MAX_SIZE] ;
    float real_res_y[MAX_SIZE] ;

    for(int i = 0; i < N; ++i)
    {
        const int   size  = dist_size(rd);
        const float alpha = dist_numbers(rd);
        const int incx = dist_inc(rd);
        const int incy = dist_inc(rd);
        
        for(int j = 0; j < MAX_SIZE; ++j)
        {
            x[j] = dist_numbers(rd);
            y[j] = dist_numbers(rd);
            real_res_y[j] = y[j];
        }

        for(int k = 1; k < size; ++k)
            real_res_y[k*incy] = std::fma(alpha, x[k*incx], real_res_y[k*incy]);

        SAXPY(alpha, x,incx, y,incy, size);

        for(int k = 1; k < size; ++k)
            REQUIRE_THAT(y[k*incy], WithinRel(real_res_y[k*incy], 1e-3f));
    }
}



TEST_CASE("DAXPY", "[BLAS 1]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const double min = -10000.0;
    const double max =  10000.0;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_int_distribution<int> dist_inc(1, 9);

    std::uniform_real_distribution<double> dist_numbers(min, max);

    double x[MAX_SIZE] ;
    double y[MAX_SIZE] ;
    double real_res_y[MAX_SIZE] ;

    for(int i = 0; i < N; ++i)
    {
        const int   size  = dist_size(rd);
        const double alpha = dist_numbers(rd);
        const int incx = dist_inc(rd);
        const int incy = dist_inc(rd);

        for(int j = 0; j < MAX_SIZE; ++j)
        {
            x[j] = dist_numbers(rd);
            y[j] = dist_numbers(rd);
            real_res_y[j] = y[j];
        }

        for(int k = 1; k < size; ++k)
            real_res_y[k*incy] = std::fma(alpha, x[k*incx], real_res_y[k*incy]);

        DAXPY(alpha, x,incx, y,incy , size);

        for(int k = 1; k < size; ++k)
            REQUIRE_THAT(y[k*incy], WithinRel(real_res_y[k*incy], 1e-3));
    }
}



TEST_CASE("SCOPY", "[BLAS 1]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const float min = -10.0f;
    const float max =  10.0f;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_int_distribution<int> dist_inc(1, 9);

    std::uniform_real_distribution<float> dist_numbers(min, max);

    float x[MAX_SIZE] ;
    float y[MAX_SIZE] ;

    for(int i = 0; i < N; ++i)
    {
        const int size = dist_size(rd);
        const int incx = dist_inc(rd);
        const int incy = dist_inc(rd);

        for(int j = 0; j < MAX_SIZE; ++j)
        {
            x[j] = dist_numbers(rd);
            y[j] = dist_numbers(rd);
        }

        SCOPY(x,incx, y,incy, size);

        for(int k = 1; k < size; ++k)
            REQUIRE_THAT(y[k*incy], WithinRel(x[k*incx], 1e-3f));
    }
}


TEST_CASE("DCOPY", "[BLAS 1]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const double min = -10.0f;
    const double max =  10.0f;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_int_distribution<int> dist_inc(1, 9);

    std::uniform_real_distribution<double> dist_numbers(min, max);

    double x[MAX_SIZE] ;
    double y[MAX_SIZE] ;

    for(int i = 0; i < N; ++i)
    {
        const int size = dist_size(rd);
        const int incx = dist_inc(rd);
        const int incy = dist_inc(rd);

        for(int j = 0; j < MAX_SIZE; ++j)
        {
            x[j] = dist_numbers(rd);
            y[j] = dist_numbers(rd);
        }


        DCOPY(x,incx, y,incy, size);

        for(int k = 1; k < size; ++k)
            REQUIRE_THAT(y[k*incy], WithinRel(x[k*incx], 1e-3));
    }
}




TEST_CASE("SSCAL", "[BLAS 1]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const float min = -10.0f;
    const float max =  10.0f;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_int_distribution<int> dist_inc(1, 9);

    std::uniform_real_distribution<float> dist_numbers(min, max);

    float x[MAX_SIZE] ;
    float y[MAX_SIZE] ;

    float real_y[MAX_SIZE] ;


    for(int i = 0; i < N; ++i)
    {
        const int size = dist_size(rd);
        const int incx = dist_inc(rd);
        const int incy = dist_inc(rd);
        const float scal = dist_numbers(rd);

        for(int j = 0; j < MAX_SIZE; ++j)
        {
            x[j] = dist_numbers(rd);
            y[j] = dist_numbers(rd);
            real_y[j] = y[i];
        }

        for(int j = 1; j < size; ++j)
        {
            real_y[incy*j] = scal*x[incx*j];
        }

        SSCAL(scal, x,incx, y,incy, size);

        for(int k = 1; k < size; ++k)
        {
            REQUIRE_THAT(y[k*incy], WithinRel(real_y[k*incy], 1e-3f));
        }
    }
}


TEST_CASE("DSCAL", "[BLAS 1]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const double min = -10.0f;
    const double max =  10.0f;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_int_distribution<int> dist_inc(1, 9);

    std::uniform_real_distribution<double> dist_numbers(min, max);

    double x[MAX_SIZE] ;
    double y[MAX_SIZE] ;

    double real_y[MAX_SIZE] ;


    for(int i = 0; i < N; ++i)
    {
        const int size = dist_size(rd);
        const int incx = dist_inc(rd);
        const int incy = dist_inc(rd);
        const double scal = dist_numbers(rd);

        for(int j = 0; j < MAX_SIZE; ++j)
        {
            x[j] = dist_numbers(rd);
            y[j] = dist_numbers(rd);
            real_y[j] = y[i];
        }

        for(int j = 1; j < size; ++j)
        {
            real_y[incy*j] = scal*x[incx*j];
        }

        DSCAL(scal, x,incx, y,incy, size);

        for(int k = 1; k < size; ++k)
        {
            REQUIRE_THAT(y[k*incy], WithinRel(real_y[k*incy], 1e-3));
        }
    }
}


TEST_CASE("SSWAP", "[BLAS 1]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const float min = -10.0f;
    const float max =  10.0f;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_int_distribution<int> dist_inc(1, 9);

    std::uniform_real_distribution<float> dist_numbers(min, max);

    float x[MAX_SIZE] ;
    float y[MAX_SIZE] ;
    float real_x[MAX_SIZE] ;
    float real_y[MAX_SIZE] ;


    for(int i = 0; i < N; ++i)
    {
        const int size = dist_size(rd);
        const int incx = dist_inc(rd);
        const int incy = dist_inc(rd);

        for(int j = 0; j < MAX_SIZE; ++j)
        {
            x[j] = dist_numbers(rd);
            y[j] = dist_numbers(rd);
            real_x[j] = x[j];
            real_y[j] = y[j];
        }

        for(int j = 1; j < size; ++j)
        {
            real_x[incx * j] = y[incy * j];
            real_y[incy * j] = x[incx * j];
        } 

        SSWAP(x, incx, y, incy, size);

        for(int k = 1; k < size; ++k)
        {
            REQUIRE_THAT(x[k*incx], WithinRel(real_x[k*incx], 1e-3f));
            REQUIRE_THAT(y[k*incy], WithinRel(real_y[k*incy], 1e-3f));

        }
    }
}

TEST_CASE("DSWAP", "[BLAS 1]")
{
    const int N = 100;
    const int p = 10;
    const int n = 20;

    const double min = -10.0;
    const double max =  10.0;

    std::random_device rd;
    std::uniform_int_distribution<int> dist_size(p, n);
    std::uniform_int_distribution<int> dist_inc(1, 9);

    std::uniform_real_distribution<double> dist_numbers(min, max);

    double x[MAX_SIZE] ;
    double y[MAX_SIZE] ;
    double real_x[MAX_SIZE] ;
    double real_y[MAX_SIZE] ;


    for(int i = 0; i < N; ++i)
    {
        const int size = dist_size(rd);
        const int incx = dist_inc(rd);
        const int incy = dist_inc(rd);

        for(int j = 0; j < MAX_SIZE; ++j)
        {
            x[j] = dist_numbers(rd);
            y[j] = dist_numbers(rd);
            real_x[j] = x[j];
            real_y[j] = y[j];
        }

        for(int j = 1; j < size; ++j)
        {
            real_x[incx * j] = y[incy * j];
            real_y[incy * j] = x[incx * j];
        } 

        DSWAP(x, incx, y, incy, size);

        for(int k = 1; k < size; ++k)
        {
            REQUIRE_THAT(x[k*incx], WithinRel(real_x[k*incx], 1e-3));
            REQUIRE_THAT(y[k*incy], WithinRel(real_y[k*incy], 1e-3));

        }
    }
}

