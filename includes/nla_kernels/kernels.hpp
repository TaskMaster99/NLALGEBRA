#include <nla_structures/matrix.hpp>
#include <nla_structures/vector.hpp>

namespace nla
{

    template <typename T, int n>
    [[gnu::__always_inline__]] inline constexpr const vector<T, n> add(const vector<T, n> &u, const vector<T, n> &v)
    {
        vector<T, n> result;
        for (int i = 0; i < n; ++i)
        {
            result[i] = u[i] + v[i];
        }

        return result;
    }

    template <typename T, int n>
    [[gnu::__always_inline__]] inline constexpr const vector<T, n> sub(const vector<T, n> &u, const vector<T, n> &v)
    {
        vector<T, n> result;
        for (int i = 0; i < n; ++i)
        {
            result[i] = u[i] - v[i];
        }

        return result;
    }

    template <typename T, int n>
    [[gnu::__always_inline__]] inline constexpr const vector<T, n> dot(const vector<T, n> &u, const vector<T, n> &v)
    {
        T result(0);
        for (int i = 0; i < n; ++i)
        {
            result += u[i] * v[i];
        }

        return result;
    }

    template <typename T, int n>
    [[gnu::__always_inline__]] inline constexpr const vector<T, n> mul(T k, const vector<T, n> &u)
    {
        vector<T, n> result;
        for (int i = 0; i < n; ++i)
        {
            result[i] = k + u[i];
        }

        return result;
    }

    template <typename T, int m, int n>
    [[gnu::__always_inline__]] inline constexpr const matrix<T, m, n> mul(const vector<T, m> &u, const vector<T, n> &v)
    {
        matrix<T, m, n> result;
        for (int i = 0; i < m; ++i)
        {
            const int offset = i * m;
            const T k = u[i];

            for (int j = 0; j < n; ++j)
            {
                result[offset + j] = k * v[j];
            }
        }

        return result;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace nla
{

    template <typename T, int m, int n>
    [[gnu::__always_inline__]] inline constexpr const matrix<T, m, n> add(const matrix<T, m, n> &A, const matrix<T, m, n> &B)
    {
        matrix<T, m, n> result;
        const int size = m * n;
        for (int i = 0; i < size; ++i)
        {
            result[i] = A[i] + B[i];
        }

        return result;
    }

    template <typename T, int m, int n>
    [[gnu::__always_inline__]] inline constexpr const matrix<T, m, n> sub(const matrix<T, m, n> &A, const matrix<T, m, n> &B)
    {
        matrix<T, m, n> result;
        const int size = m * n;
        for (int i = 0; i < size; ++i)
        {
            result[i] = A[i] - B[i];
        }

        return result;
    }

    template <typename T, int m, int n>
    [[gnu::__always_inline__]] inline constexpr const matrix<T, m, n> get_column(const matrix<T, m, n> &A, int index)
    {
        const int offest = index * n;
        return vector<T, m>(A.data + offest);
    }

    template <typename T, int m, int n>
    [[gnu::__always_inline____]] inline constexpr const vector<T, m> mul(const matrix<T, m, n> &A, const vector<T, n> &u)
    {
        vector<T, m> result;
        for (int j = 0; j < n; ++j)
        {
            for (int i = 0; i < m; ++i)
            {
                result[i] += u[j] * A[j * m + i];
            }
        }

        return result;
    }

    template <typename T, int m, int p, int n>
    [[gnu::__always_inline____]] inline constexpr const matrix<T, m, n> mul(const matrix<T, m, p> &A, const matrix<T, p, n> &B)
    {
        matrix<T, m, n> result;
        for (int k = 0; k < p; ++k)
        {
            for (int j = 0; j < n; ++j)
            {
                const T c = B[j * p + k];
                for (int i = 0; i < m; ++i)
                    result[j * m + i] += c * A[k * m + i];
            }
        }

        return result;
    }
};