#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <nla_kernels/kernels.hpp>
#include <kernel/dot.hpp>

using namespace Catch::Matchers;

template<typename T>
void matching_matrix_test(const NLA::DenseMatrix<T>& A, const T* real_res)
{
    for(int j = 0; j < A.n; ++j)
    {
        for(int i = 0; i < A.m; ++i)
        {
            REQUIRE_THAT(A(i,j), WithinAbs(real_res[i*A.n + j], EPSILON32_LV1));
        }
    }
}

template<typename T>
void matching_matrix_test(const NLA::DenseMatrix<T>& A, const NLA::DenseMatrix<T>& B, T tolerance)
{
    for(int j = 0; j < A.n; ++j)
    {
        for(int i = 0; i < A.m; ++i)
        {
            REQUIRE_THAT(A(i,j), WithinAbs(B(i,j), tolerance));
        }
    }
}

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

TEST_CASE("Matrix Implemantation", "[Matrix Constructors]")
{
    NLA::DenseMatrix<float> A = 
    {
        3, 3,
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    print(A);
}

TEST_CASE("Matrix kernels", "[LU Decompostion]")
{
    const float a[9] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f};

    const NLA::DenseMatrix<float> A(3, 3, a);

    NLA::DenseMatrix<float> U0;
    NLA::DenseMatrix<float> L0;

    NLA::LU_Decomposition(A, L0, U0);

    const float real_res_U [9] = 
    {
        1.0f, 2.0f, 3.0f,
        0.0f,-3.0f,-6.0f,
        0.0f, 0.0f, 0.0f
    };

    const float real_res_L [9] = 
    {
        1.0f, 0.0f, 0.0f,
        4.0f, 1.0f, 0.0f,
        7.0f, 2.0f, 1.0f
    };

    matching_matrix_test(U0, real_res_U);
    matching_matrix_test(L0, real_res_L);

}


TEST_CASE("Matrix kernels", "[LU Decompostion with permutation]")
{
    for(int N = 0; N < 1; ++N)
    {
        const NLA::DenseMatrix<float> A = NLA::random<float>(10, 10, -100.0f, 100.0f);
        NLA::DenseMatrix<float> P;
        NLA::DenseMatrix<float> U;
        NLA::DenseMatrix<float> L;

        NLA::PLU_Decomposition(A,P,L, U);

        const NLA::DenseMatrix<float> LH = NLA::mul(P, A);
        const NLA::DenseMatrix<float> RH = NLA::mul(L, U);

        matching_matrix_test(LH,RH, EPSILON32_LV1);

    }
}