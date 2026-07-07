#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <nla_kernels/kernels.hpp>

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

TEST_CASE("Matrix kernels", "[LU Decompostion]")
{
    const float a[9] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f};

    const NLA::DenseMatrix<float> A(a, 3, 3);

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
    for(int N = 0; N < 10000; ++N)
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