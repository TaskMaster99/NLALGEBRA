#pragma once

#include <nla_tools.hpp>

namespace nla
{
    /**
     * @struct
     * @brief vector n
     * @param num_element number of elements
     * @param data sets of scalar
     */
    template <typename T, int n>
    struct vector
    {
        int num_element;
        T data[n];

        constexpr vector() : num_element(n) {};
        constexpr vector(const T k) : num_element(n)
        {
            for (int i = 0; i < num_element; ++i)
                data[i] = k;
        }
        constexpr vector(const T *data) : num_element(n)
        {
            for (int i = 0; i < num_element; ++i)
                this->data[i] = data[i];
        }

        constexpr vector(const vector<T, n> &u) : num_element(u.num_element)
        {
            for (int i = 0; i < num_element; ++i)
                this->data[i] = u.data[i];
        }

        [[gnu::__always_inline__]] inline constexpr vector &operator=(const T *data)
        {
            for (int i = 0; i < num_element; ++i)
                this->data[i] = data[i];

            return *this;
        }

        [[gnu::__always_inline__]] inline constexpr vector &operator=(const vector<T, n> &u)
        {
            for (int i = 0; i < num_element; ++i)
                this->data[i] = data[i];

            return *this;
        }

        [[gnu::__always_inline__]] inline constexpr T &operator[](int i)
        {
            ASSERTM(i < num_element, "Out of border !!\n");
            return data[i];
        }

        [[gnu::__always_inline__]] inline constexpr T operator[](int i) const
        {
            ASSERTM(i < num_element, "Out of border !!\n");
            return data[i];
        }
    };
};