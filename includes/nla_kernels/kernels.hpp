#include <nla_structures/matrix.hpp>
#include <nla_structures/vector.hpp>

namespace NLA
{

    template <typename T>
    [[gnu::always_inline]] inline const DenseVector<T> add(const DenseVector<T> &u, const DenseVector<T> &v)
    {
        DenseVector<T> w(u.n);
        for (int i = 0; i < u.n; ++i)
            w(i) = u(i) + v(i);

        return w;
    }

    template <typename T>
    [[gnu::always_inline]] inline const DenseVector<T> sub(const DenseVector<T> &u, const DenseVector<T> &v)
    {
        DenseVector<T> w(u.n);
        for (int i = 0; i < u.n; ++i)
            w(i) = u(i) - v(i);

        return w;
    }

    template <typename T>
    [[gnu::always_inline]] inline const DenseVector<T> axpy(const DenseVector<T> &u, T k, const DenseVector<T> &v)
    {
        DenseVector<T> w(u.n);
        for (int i = 0; i < u.n; ++i)
            w(i) = u(i) * k + v(i);

        return w;
    }

    template <typename T>
    [[gnu::always_inline]] inline const T dot(const DenseVector<T> &u, const DenseVector<T> &v)
    {
        T d(0);
        for (int i = 0; i < u.n; ++i)
            d += u(i) * v(i);

        return d;
    }

    template <typename T>
    [[gnu::always_inline]] inline const DenseVector<T> mul(T k, const DenseVector<T> &u)
    {
        DenseVector<T> w(u.n);
        for (int i = 0; i < u.n; ++i)
            w(i) = k * u(i);

        return w;
    }

    template <typename T>
    [[gnu::always_inline]] inline const DenseMatrix<T> mul(const DenseVector<T> &u, const DenseVector<T> &v)
    {
        DenseMatrix<T> A(u.n, v.n);
        for (int i = 0; i < u.n; ++i)
        {
            const int offset = i * u.n;
            const T k = u(i);

            for (int j = 0; j < v.n; ++j)
                A(j, i) = k * v(j);
        }

        return A;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NLA
{

    template <typename T>
    [[gnu::always_inline]] inline const DenseMatrix<T> identity(int m, int n)
    {
        DenseMatrix<T> C(m, n);
        for (int i = 0; i < m; ++i)
            C(i, i) = T(1);

        return C;
    }

    template <typename T>
    inline void print(const DenseMatrix<T> &A)
    {
        for (int i = 0; i < A.m; ++i)
        {
            fmt::print("[ ");
            for (int j = 0; j < A.n; ++j)
            {
                fmt::print("{} ", A(i, j));
            }
            fmt::println("]");
        }
        fmt::println("");
    }

    template <typename T>
    [[gnu::always_inline]] inline const DenseMatrix<T> add(const DenseMatrix<T> &A, const DenseMatrix<T> &B)
    {
        DenseMatrix<T> C(A.num_row, A.num_column);
        const int size = A.num_row + A.num_column;
        for (int i = 0; i < size; ++i)
        {
            C[i] = A[i] + B[i];
        }

        return C;
    }

    template <typename T>
    [[gnu::always_inline]] inline const DenseMatrix<T> sub(const DenseMatrix<T> &A, const DenseMatrix<T> &B)
    {
        DenseMatrix<T> C(A.num_row, A.num_column);
        const int size = A.num_row + A.num_column;
        for (int i = 0; i < size; ++i)
        {
            C[i] = A[i] - B[i];
        }

        return C;
    }

    template <typename T>
    [[gnu::always_inline]] inline const DenseMatrix<T> get_column(const DenseMatrix<T> &A, int index)
    {
        const int offest = index * A.n;
        return DenseVector<T>(A.data + offest);
    }

    template <typename T>
    [[gnu::always_inline]] inline const DenseVector<T> mul(const DenseMatrix<T> &A, const DenseVector<T> &u)
    {
        DenseVector<T> b(A.m);
        for (int j = 0; j < u.n; ++j)
        {
            for (int i = 0; i < A.m; ++i)
            {
                b(i) += u(j) * A(i, j);
            }
        }

        return b;
    }

    template <typename T>
    [[gnu::always_inline]] inline const DenseMatrix<T> mul(const DenseMatrix<T> &A, const DenseMatrix<T> &B)
    {
        ASSERTM(A.n == B.m, "Can't process GEMM kernel on incompatible matrices (chose a matrix A and B where number of column of A is equal to the number of row of B).\n");

        const int m = A.m;
        const int n = B.n;
        const int p = A.n;

        DenseMatrix<T> C(m, n);
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < p; ++k)
            {
                const T c = B(k, j);
                for (int i = 0; i < m; ++i)
                    C(i, j) += c * A(i, k);
            }
        }
        return C;
    }

    template <typename T>
    [[gnu::always_inline]] inline const DenseMatrix<T> pivot(const DenseMatrix<T> &A, int h, int l)
    {
        DenseMatrix<T> P(A);
        for (int j = 0; j < A.n; ++j)
        {
            const T piv = A(h, j);
            P(h, j) = A(l, j);
            P(l, j) = piv;
        }

        return P;
    }

    template <typename T>
    [[gnu::always_inline]] inline void LU_Decomposition(const DenseMatrix<T> &A, DenseMatrix<T> &L, DenseMatrix<T> &U)
    {
        U = A;
        L = identity<T>(A.m, A.n);
        T k(0);
        for (int l = 0; l < U.m; ++l)
        {
            if(U(l, l) == T(0))
            {
                int offset = l + 1;
                do
                {
                    if (U(offset, l) != T(0))
                    {
                        U = pivot(U, offset, l);
                        swap(L(offset, l-1), L(l, l-1));
                        break;
                    }

                } while (++offset < U.n);
            }

            for (int d = l + 1; d < U.m; ++d)
            {
                k = U(d, l) / U(l, l);
                L(d, l) = k;

                for (int c = l; c < U.n; ++c)
                {
                    U(d, c) -= k * U(l, c);
                }
            }
        }
    }

};