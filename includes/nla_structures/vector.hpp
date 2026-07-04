#pragma once

#include <nla_tools.hpp>

namespace NLA
{
    /**
     * @struct
     * @brief DenseVector n
     * @param n number of elements
     * @param data sets of scalar
     */
    template <typename T>
    struct DenseVector
    {
        int n;
        T *data;

        DenseVector() : n(4), data((T *)std::malloc(4 * sizeof(T)))
        {
            for (int i = 0; i < n; ++i)
                data[i] = static_cast<T>(0);
        };
        DenseVector(const int nl) : n(nl), data((T *)std::malloc(nl * sizeof(T)))
        {
            for (int i = 0; i < n; ++i)
                data[i] = static_cast<T>(0);
        }
        DenseVector(const T k, const int nl) : n(nl), data((T *)std::malloc(nl * sizeof(T)))
        {
            for (int i = 0; i < n; ++i)
                data[i] = k;
        }
        DenseVector(const T *data, const int nl) : n(nl), data((T *)std::malloc(nl * sizeof(T)))
        {
            for (int i = 0; i < n; ++i)
                this->data[i] = data[i];
        }

        DenseVector(const DenseVector<T> &u) : n(u.n), data((T *)std::malloc(u.n * sizeof(T)))
        {
            for (int i = 0; i < n; ++i)
                this->data[i] = u.data[i];
        }

        ~DenseVector()
        {
            if (data)
                free(data);
        }

        [[gnu::always_inline]] inline DenseVector &operator=(const T *data)
        {
            for (int i = 0; i < n; ++i)
                this->data[i] = data[i];

            return *this;
        }

        [[gnu::always_inline]] inline DenseVector &operator=(const DenseVector<T> &u)
        {
            for (int i = 0; i < n; ++i)
                this->data[i] = data[i];

            return *this;
        }

        [[gnu::always_inline]] inline T &operator[](int i)
        {
            ASSERTM(i < n, "Out of border !!\n");
            return data[i];
        }

        [[gnu::always_inline]] inline T operator[](int i) const
        {
            ASSERTM(i < n, "Out of border !!\n");
            return data[i];
        }

        [[gnu::always_inline]] inline T &operator()(int i)
        {
            ASSERTM(i < n, "Out of border !!\n");
            return data[i];
        }

        [[gnu::always_inline]] inline T operator()(int i) const
        {
            ASSERTM(i < n, "Out of border !!\n");
            return data[i];
        }
    };
};