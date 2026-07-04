#pragma once

#include <nla_tools.hpp>

namespace NLA
{

    /**
     * @struct
     * @brief Column Major Matrix mxn
     */
    template <typename T>
    struct DenseMatrix
    {
        int m = 0;
        int n = 0;
        T *data = nullptr;

        DenseMatrix() {}
        DenseMatrix(const T k, int ml, int nl) : m(ml), n(nl), data((T *)std::malloc(ml * nl * sizeof(T)))
        {
            const int size = m * n;
            data = (T *)std::malloc(size * sizeof(T));
            for (int i = 0; i < size; ++i)
                data[i] = static_cast<T>(k);
        }
        DenseMatrix(int ml, int nl) : m(ml), n(nl), data((T *)std::malloc(ml * nl * sizeof(T)))
        {
            const int size = m * n;
            data = (T *)std::malloc(size * sizeof(T));
            for (int i = 0; i < size; ++i)
                data[i] = static_cast<T>(0);
        }

        DenseMatrix(const T *data, int ml, int nl) : m(ml), n(nl), data((T *)std::malloc(ml * nl * sizeof(T)))
        {
            for (int j = 0; j < n; ++j)
                for (int i = 0; i < m; ++i)
                    this->data[j * m + i] = data[i * n + j];
        }

        DenseMatrix(const DenseMatrix<T> &A) : m(A.m), n(A.n), data((T *)std::malloc(A.m * A.n * sizeof(T)))
        {
            const int size = m * n;
            for (int i = 0; i < size; ++i)
                this->data[i] = A.data[i];
        }

        ~DenseMatrix()
        {
            if (data)
                free(data);
        }

        [[gnu::always_inline]] inline DenseMatrix &operator=(const T *data)
        {
            const int size = m * n;
            for (int i = 0; i < size; ++i)
                this->data[i] = data[i];

            return *this;
        }

        [[gnu::always_inline]] inline DenseMatrix &operator=(const DenseMatrix<T> &A)
        {
            m = A.m;
            n = A.n;

            const int size = m * n;

            data = (T *)std::malloc(m * n * sizeof(T));

            for (int i = 0; i < size; ++i)
                this->data[i] = A.data[i];

            return *this;
        }

        [[gnu::always_inline]] inline T &operator[](int i)
        {
            ASSERTM(i < (m * n), "Out of border !!\n");
            return data[i];
        }

        [[gnu::always_inline]] inline T operator[](int i) const
        {
            ASSERTM(i < (m * n), "Out of border !!\n");
            return data[i];
        }

        [[gnu::always_inline]] inline T &operator()(int i, int j)
        {
            ASSERTM((j * m + i) < (m * n), "Out of border !!\n");
            return data[j * m + i];
        }

        [[gnu::always_inline]] inline T operator()(int i, int j) const
        {
            ASSERTM((j * m + i) < (m * n), "Out of border !!\n");
            return data[j * m + i];
        }
    };

};