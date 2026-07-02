#pragma once

#include <nla_tools.hpp>

namespace nla
{
    /**
     * @struct
     * @brief Column Major Matrix mxn
     * @param num_row the
     */
    template <typename T, int m, int n>
    struct matrix
    {
        int num_row;
        int num_column;
        T data[m * n];

        constexpr matrix() : num_row(m), num_column(n)
        {
            const int size = m * n;
            for (int i = 0; i < size; ++i)
                data[i] = static_cast<T>(0);
        }
        constexpr matrix(const T k)
        {
            const int size = m * n;
            for (int i = 0; i < size; ++i)
                data[i] = k;
        }
        constexpr matrix(const T *data)
        {
            for (int j = 0; j < n; ++j)
                for (int i = 0; i < m; ++i)
                    this->data[j * m + i] = data[i * n + j];
        }

        constexpr matrix(const matrix<T, m, n> &A)
        {
            const int size = m * n;
            for (int i = 0; i < size; ++i)
                this->data[i] = A.data[i];
        }

        [[gnu::__always_inline__]] inline constexpr matrix &operator=(const T *data)
        {
            const int size = m * n;
            for (int i = 0; i < size; ++i)
                this->data[i] = data[i];

            return *this;
        }

        [[gnu::__always_inline__]] inline constexpr matrix &operator=(const matrix<T, m, n> &A)
        {
            const int size = m * n;
            for (int i = 0; i < size; ++i)
                this->data[i] = A.data[i];

            return *this;
        }

        [[gnu::__always_inline__]] inline constexpr T &operator[](int i)
        {
            ASSERTM(i < (n * m), "Out of border !!\n");
            return data[i];
        }

        [[gnu::__always_inline__]] inline constexpr T operator[](int i) const
        {
            ASSERTM(i < (n * m), "Out of border !!\n");
            return data[i];
        }
    };
};