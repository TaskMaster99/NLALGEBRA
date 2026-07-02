#include <catch2/catch_test_macros.hpp>
#include <nla_kernels/kernels.hpp>

TEST_CASE("Matrix kernels", "[Matrix]")
{
    float aa[9] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f};
    nla::matrix<float, 3, 3> A = aa;

    REQUIRE(A[0] == 1.0f);
    REQUIRE(A[1] == 4.0f);
    REQUIRE(A[2] == 7.0f);

    REQUIRE(A[3] == 2.0f);
    REQUIRE(A[4] == 5.0f);
    REQUIRE(A[5] == 8.0f);

    REQUIRE(A[6] == 3.0f);
    REQUIRE(A[7] == 6.0f);
    REQUIRE(A[8] == 9.0f);

    float bb[9] = {
        5.0f, 2.0f, 3.0f,
        4.0f, 12.0f, 6.0f,
        -7.0f, 8.0f, -9.0f};

    nla::matrix<float, 3, 3> B = bb;
    REQUIRE(B[0] == 5.0f);
    REQUIRE(B[1] == 4.0f);
    REQUIRE(B[2] == -7.0f);

    REQUIRE(B[3] == 2.0f);
    REQUIRE(B[4] == 12.0f);
    REQUIRE(B[5] == 8.0f);

    REQUIRE(B[6] == 3.0f);
    REQUIRE(B[7] == 6.0f);
    REQUIRE(B[8] == -9.0f);

    nla::matrix<float, 3, 3> C = nla::mul<float, 3, 3>(A, B);

    REQUIRE(C[0] == -8.0f);
    REQUIRE(C[1] == -2.0f);
    REQUIRE(C[2] == 4.0f);

    REQUIRE(C[3] == 50.0f);
    REQUIRE(C[4] == 116.0f);
    REQUIRE(C[5] == 182.0f);

    REQUIRE(C[6] == -12.0f);
    REQUIRE(C[7] == -12.0f);
    REQUIRE(C[8] == -12.0f);

    float xx[3] = {
        -11.0f,
        2.0f,
        73.0f};

    nla::vector<float, 3> x = xx;

    REQUIRE(x[0] == -11.0f);
    REQUIRE(x[1] == 2.0f);
    REQUIRE(x[2] == 73.0f);

    nla::vector<float, 3> b = nla::mul<float, 3, 3>(A, x);

    REQUIRE(b[0] == 212.0f);
    REQUIRE(b[1] == 404.0f);
    REQUIRE(b[2] == 596.0f);
}