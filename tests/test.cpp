#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <nla_kernels/kernels.hpp>

using namespace Catch::Matchers;

TEST_CASE("Matrix kernels", "[LU Decompostion]")
{
    const float a[9] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f};

    const NLA::DenseMatrix<float> A(a, 3, 3);

    NLA::DenseMatrix<float> U0;
    NLA::DenseMatrix<float> L0;

    NLA::DenseMatrix<float> P;
    NLA::DenseMatrix<float> U1;
    NLA::DenseMatrix<float> L1;

    NLA::LU_Decomposition(A, L0, U0);


    REQUIRE(U0[0] == 1.0f);REQUIRE(U0[3] ==  2.0f);REQUIRE(U0[6] ==   3.0f);
    REQUIRE(U0[1] == 0.0f);REQUIRE(U0[4] == -3.0f);REQUIRE(U0[7] ==  -6.0f);
    REQUIRE(U0[2] == 0.0f);REQUIRE(U0[5] ==  0.0f);REQUIRE(U0[8] ==   0.0f);
}


TEST_CASE("Matrix kernels", "[LU Decompostion with permutation]")
{
    const float a[16] = {
        1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 2.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 3.0f, 1.0f};

    const float c[25] = {
     1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     2.0f, 3.0f, 3.0f, 3.0f, 3.0f,
     1.0f, 4.0f, 6.0f, 6.0f, 6.0f,
     1.0f, 1.0f, 5.0f, 8.0f, 8.0f,
     1.0f, 1.0f, 1.0f, 6.0f, 10.0f};

    const NLA::DenseMatrix<float> A(a, 4, 4);
    const NLA::DenseMatrix<float> C(c, 5, 5);

    NLA::DenseMatrix<float> P1;
    NLA::DenseMatrix<float> U1;
    NLA::DenseMatrix<float> L1;

    NLA::PLU_Decomposition(A, P1, L1, U1);

    NLA::DenseMatrix<float> P2;
    NLA::DenseMatrix<float> U2;
    NLA::DenseMatrix<float> L2;

    NLA::PLU_Decomposition(C, P2, L2, U2);

    REQUIRE(U1[0] == 1.0f);REQUIRE(U1[4] ==  0.0f);REQUIRE(U1[8]  ==   1.0f);REQUIRE(U1[12] ==  1.0f);
    REQUIRE(U1[1] == 0.0f);REQUIRE(U1[5] ==  1.0f);REQUIRE(U1[9]  ==   1.0f);REQUIRE(U1[13] ==  1.0f);
    REQUIRE(U1[2] == 0.0f);REQUIRE(U1[6] ==  0.0f);REQUIRE(U1[10] ==  -2.0f);REQUIRE(U1[14] == -1.0f);
    REQUIRE(U1[3] == 0.0f);REQUIRE(U1[7] ==  0.0f);REQUIRE(U1[11] ==   0.0f);REQUIRE(U1[15] == -0.5f);


    REQUIRE(L1[0] == 1.0f);REQUIRE(L1[4] == 0.0f);REQUIRE(L1[8]  ==  0.0f);REQUIRE(L1[12] == 0.0f);
    REQUIRE(L1[1] == 0.0f);REQUIRE(L1[5] == 1.0f);REQUIRE(L1[9]  ==  0.0f);REQUIRE(L1[13] == 0.0f);
    REQUIRE(L1[2] == 0.0f);REQUIRE(L1[6] == 2.0f);REQUIRE(L1[10] ==  1.0f);REQUIRE(L1[14] == 0.0f);
    REQUIRE(L1[3] == 0.0f);REQUIRE(L1[7] == 0.0f);REQUIRE(L1[11] == -1.5f);REQUIRE(L1[15] == 1.0f);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    REQUIRE(U2[0] == 1.0f);REQUIRE(U2[5] == 1.0f);REQUIRE(U2[10]  ==  1.0f);REQUIRE(U2[15] == 1.0f);REQUIRE(U2[20] == 1.0f);
    REQUIRE(U2[1] == 0.0f);REQUIRE(U2[6] == 1.0f);REQUIRE(U2[11]  ==  1.0f);REQUIRE(U2[16] == 1.0f);REQUIRE(U2[21] == 1.0f);
    REQUIRE(U2[2] == 0.0f);REQUIRE(U2[7] == 0.0f);REQUIRE(U2[12]  ==  2.0f);REQUIRE(U2[17] == 2.0f);REQUIRE(U2[22] == 2.0f);
    REQUIRE(U2[3] == 0.0f);REQUIRE(U2[8] == 0.0f);REQUIRE(U2[13]  ==  0.0f);REQUIRE(U2[18] == 3.0f);REQUIRE(U2[23] == 3.0f);
    REQUIRE(U2[4] == 0.0f);REQUIRE(U2[9] == 0.0f);REQUIRE(U2[14]  ==  0.0f);REQUIRE_THAT(U2[19], WithinAbs(0.0f, EPSILON32_LV2));REQUIRE(U2[24] == 4.0f);


    REQUIRE(L2[0] == 1.0f);REQUIRE(L2[5] == 0.0f);REQUIRE(L2[10]  ==  0.0f);REQUIRE(L2[15] == 0.0f);REQUIRE(L2[20] == 0.0f);
    REQUIRE(L2[1] == 2.0f);REQUIRE(L2[6] == 1.0f);REQUIRE(L2[11]  ==  0.0f);REQUIRE(L2[16] == 0.0f);REQUIRE(L2[21] == 0.0f);
    REQUIRE(L2[2] == 1.0f);REQUIRE(L2[7] == 3.0f);REQUIRE(L2[12]  ==  1.0f);REQUIRE(L2[17] == 0.0f);REQUIRE(L2[22] == 0.0f);
    REQUIRE(L2[3] == 1.0f);REQUIRE(L2[8] == 0.0f);REQUIRE(L2[13]  ==  2.0f);REQUIRE(L2[18] == 1.0f);REQUIRE(L2[23] == 0.0f);
    REQUIRE(L2[4] == 1.0f);REQUIRE(L2[9] == 0.0f);REQUIRE(L2[14]  ==  0.0f);REQUIRE_THAT(L2[19], WithinAbs(1.66666667f, EPSILON32_LV1));REQUIRE(L2[24] == 1.0f);

}