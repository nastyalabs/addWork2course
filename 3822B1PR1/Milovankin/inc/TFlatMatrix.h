#pragma once

#include <string>
#include <cstddef>
#include <concepts>
#include <algorithm>
#include <iostream>
#include <exception>

// Concept to check if typename supports required matrix operations (+, -, *)
// template <typename T>
// concept MatrixOperations = requires(T a, T b)
// {
//     { a * b } -> std::same_as<T>;
//     { a + b } -> std::same_as<T>;
//     { a - b } -> std::same_as<T>;
// };

template <typename T>
class TFlatMatrix
{
private:
    size_t sz;
    T* vals;

    // For copy-and-swap idiom
    friend void swap(TFlatMatrix<T>& lhs, TFlatMatrix<T>& rhs)
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.sz, rhs.vals);
    }

public:
    TFlatMatrix() = delete;

    TFlatMatrix(size_t sz) :
        sz(sz),
        vals(new T[sz * sz]{})
    { }

    TFlatMatrix(const TFlatMatrix<T>& other) :
        sz(other.sz),
        vals(new T[sz * sz])
    {
        std::copy(other.vals, other.vals + sz * sz, vals);
    }

    TFlatMatrix(TFlatMatrix<T>&& other) :
        sz(other.sz),
        vals(other.vals)
    {
        other.sz = 0;
        other.vals = nullptr;
    }

    TFlatMatrix& operator=(const TFlatMatrix<T>& other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    TFlatMatrix& operator=(TFlatMatrix<T>&& other)
    {
        swap(*this, other);
        return *this;
    }

    ~TFlatMatrix()
    {
        delete[] vals;
    }

    size_t size() const
    {
        return sz;
    }

    const T& at(size_t i, size_t j) const
    {
        if (i >= sz || j >= sz)
            throw std::out_of_range("Index out of bounds");
        return vals[i * sz + j];
    }

    T& at(size_t i, size_t j)
    {
        if (i >= sz || j >= sz)
            throw std::out_of_range("Index out of bounds");
        return vals[i * sz + j];
    }

    TFlatMatrix operator*(const TFlatMatrix& other) const
        //requires MatrixOperations<T>
    {
        TFlatMatrix result(sz);

        for (size_t i = 0; i < sz; i++)
        {
            for (size_t j = 0; j < sz; j++)
            {
                T sm{};
                for (size_t k = 0; k < sz; k++) {
                    sm += at(i, k) * other.at(k, j);
                }
                result.at(i, j) = sm;
            }
        }

        return result;
    }

    TFlatMatrix operator+(const TFlatMatrix& other) const
        //requires MatrixOperations<T>
    {
        TFlatMatrix result(sz);

        for (size_t i = 0; i < sz; i++)
        {
            for (size_t j = 0; j < sz; j++)
            {
                result.at(i, j) = at(i, j) + other.at(i, j);
            }
        }
        return result;
    }

    TFlatMatrix operator-(const TFlatMatrix& other) const
    {
        TFlatMatrix result(sz);

        for (size_t i = 0; i < sz; i++)
        {
            for (size_t j = 0; j < sz; j++)
            {
                result.at(i, j) = at(i, j) - other.at(i, j);
            }
        }
        return result;
    }

    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const TFlatMatrix& m)
    {
        for (size_t i = 0; i < m.size(); i++)
        {
            for (size_t j = 0; j < m.size(); j++)
            {
                os << m.at(j, i) << " ";
            }
            os << std::endl;
        }
        return os;
    }
};