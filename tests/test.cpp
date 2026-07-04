#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <nla_kernels/kernels.hpp>

TEST_CASE("Matrix kernels", "[Matrix]")
{
    const float aa[9] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f};

    const float aaa[9] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f};

    const float aaaa[9] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 8.0f, 6.0f,
        7.0f, 8.0f, 9.0f};

    const float bb[9] = {
        5.0f, 2.0f, 3.0f,
        4.0f, 12.0f, 6.0f,
        -7.0f, 8.0f, -9.0f};

    const float xx[3] = {
        -11.0f,
        2.0f,
        73.0f};


    const NLA::DenseMatrix<float> A(aa, 3, 3);
    const NLA::DenseMatrix<float> B(bb, 3, 3);
    const NLA::DenseMatrix<float> C = NLA::mul<float>(A, B);
    const NLA::DenseVector<float> x(xx, 3);
    const NLA::DenseVector<float> b = NLA::mul<float>(A, x);
    const NLA::DenseMatrix<float> AA(aaa, 3, 3);
    const NLA::DenseMatrix<float> AAA(aaaa, 3, 3);

    const NLA::DenseMatrix<float> P = NLA::pivot(AA, 1, 2);

    NLA::DenseMatrix<float> U;
    NLA::DenseMatrix<float> L;

    NLA::LU_Decomposition(AAA, L, U);

    REQUIRE(A[0] == 1.0f);REQUIRE(A[3] == 2.0f);REQUIRE(A[6] == 3.0f);
    REQUIRE(A[1] == 4.0f);REQUIRE(A[4] == 5.0f);REQUIRE(A[7] == 6.0f);
    REQUIRE(A[2] == 7.0f);REQUIRE(A[5] == 8.0f);REQUIRE(A[8] == 9.0f);

    REQUIRE(B[0] ==  5.0f);REQUIRE(B[3] ==  2.0f);REQUIRE(B[6] ==  3.0f);
    REQUIRE(B[1] ==  4.0f);REQUIRE(B[4] == 12.0f);REQUIRE(B[7] ==  6.0f);
    REQUIRE(B[2] == -7.0f);REQUIRE(B[5] ==  8.0f);REQUIRE(B[8] == -9.0f);

    REQUIRE(C[0] == -8.0f);
    REQUIRE(C[1] == -2.0f);
    REQUIRE(C[2] == 4.0f);

    REQUIRE(C[3] == 50.0f);
    REQUIRE(C[4] == 116.0f);
    REQUIRE(C[5] == 182.0f);

    REQUIRE(C[6] == -12.0f);
    REQUIRE(C[7] == -12.0f);
    REQUIRE(C[8] == -12.0f);

    REQUIRE(x[0] == -11.0f);
    REQUIRE(x[1] == 2.0f);
    REQUIRE(x[2] == 73.0f);

    REQUIRE(b[0] == 212.0f);
    REQUIRE(b[1] == 404.0f);
    REQUIRE(b[2] == 596.0f);

    REQUIRE(P[0] == 1.0f);REQUIRE(P[3] == 2.0f);REQUIRE(P[6] == 3.0f);
    REQUIRE(P[1] == 7.0f);REQUIRE(P[4] == 8.0f);REQUIRE(P[7] == 9.0f);
    REQUIRE(P[2] == 4.0f);REQUIRE(P[5] == 5.0f);REQUIRE(P[8] == 6.0f);

    REQUIRE(U[0] == 1.0f);REQUIRE(U[3] ==  2.0f);REQUIRE(U[6] ==   3.0f);
    REQUIRE(U[1] == 0.0f);REQUIRE(U[4] == -6.0f);REQUIRE(U[7] == -12.0f);
    REQUIRE(U[2] == 0.0f);REQUIRE(U[5] ==  0.0f);REQUIRE(U[8] ==  -6.0f);
    

    REQUIRE(L[0] == 1.0f);REQUIRE(L[3] == 0.0f);REQUIRE(L[6] == 0.0f);
    REQUIRE(L[1] == 7.0f);REQUIRE(L[4] == 1.0f);REQUIRE(L[7] == 0.0f);
    REQUIRE(L[2] == 4.0f);REQUIRE(L[5] == 0.0f);REQUIRE(L[8] == 1.0f);
}