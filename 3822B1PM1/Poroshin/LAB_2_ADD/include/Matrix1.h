// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector too large");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector too large");
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(v, *this);
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return(*this);
        if (sz != v.sz) {
            T* tmp = new T[v.sz];
            delete[] pMem;
            sz = v.sz;
            pMem = tmp;
        }
        std::copy(v.pMem, v.pMem + sz, pMem);
        return(*this);
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(v, *this);
        return(*this);
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return(pMem[ind]);
    }
    const T& operator[](size_t ind) const
    {
        return(pMem[ind]);
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if ((ind >= sz) || (ind < 0))
            throw out_of_range("Invalid index");
        else
            return(pMem[ind]);
    }
    const T& at(size_t ind) const
    {
        if ((ind >= sz) || (ind < 0))
            throw out_of_range("Invalid index");
        else
            return(pMem[ind]);
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
            return(0);
        for (size_t i = 0; i < sz; i++)
            if (pMem[i] != v.pMem[i])
                return(0);
        return(1);
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return(!(*this == v));
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector A(sz);
        for (size_t i = 0; i < sz; i++)
            A.pMem[i] = pMem[i] + val;
        return(A);
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector A(sz);
        for (size_t i = 0; i < sz; i++)
            A.pMem[i] = pMem[i] - val;
        return(A);
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector A(sz);
        for (size_t i = 0; i < sz; i++)
            A.pMem[i] = pMem[i] * val;
        return(A);
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        TDynamicVector A(sz);
        if (sz != v.sz)
            throw out_of_range("Different vector sizes");
        else
            for (size_t i = 0; i < sz; i++)
                A.pMem[i] = pMem[i] + v.pMem[i];
        return(A);
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        TDynamicVector A(sz);
        if (sz != v.sz)
            throw out_of_range("Different vector sizes");
        else
            for (size_t i = 0; i < sz; i++)
                A.pMem[i] = pMem[i] - v.pMem[i];
        return(A);
    }
    T operator*(const TDynamicVector& v)
    {
        T sum = 0;
        if (sz != v.sz)
            throw out_of_range("Different vector sizes");
        else
            for (size_t i = 0; i < sz; i++)
                sum += pMem[i] * v.pMem[i];
        return(sum);
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    size_t GetSize(void) const
    {
        return(sz);
    }

    TDynamicVector ReSizeV(size_t size)
    {
        if ((size == 0) || (size > MAX_VECTOR_SIZE))
            throw out_of_range("Invalid size");
        if (size == sz)
            return(*this);
        if (size > sz) {
            TDynamicVector A(size);
            for (size_t i = 0; i < sz; i++) {
                A[i] = (*this)[i];
            }
            return(A);
        }
        else {
            TDynamicVector B(size);
            for (size_t i = 0; i < size; i++) {
                B[i] = (*this)[i];
            }
            return(B);
        }
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz > MAX_MATRIX_SIZE)
            throw out_of_range("Matrix too large");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at;
    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return(TDynamicVector<TDynamicVector<T>>::operator==(m));
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix A(sz);
        for (size_t i = 0; i < sz; i++)
            A.pMem[i] = pMem[i] * val;
        return(A);
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        TDynamicMatrix A(sz);
        for (size_t i = 0; i < sz; i++)
            A.pMem[i] = pMem[i] * v;
        return(A);
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& v)
    {
        TDynamicMatrix A(sz);
        if (sz != v.sz)
            throw out_of_range("Different matrix sizes");
        else
            for (size_t i = 0; i < sz; i++)
                A.pMem[i] = pMem[i] + v.pMem[i];
        return(A);
    }
    TDynamicMatrix operator-(const TDynamicMatrix& v)
    {
        TDynamicMatrix A(sz);
        if (sz != v.sz)
            throw out_of_range("Different matrix sizes");
        else
            for (size_t i = 0; i < sz; i++)
                A.pMem[i] = pMem[i] - v.pMem[i];
        return(A);
    }
    TDynamicMatrix operator*(const TDynamicMatrix& v)
    {
        TDynamicMatrix A(sz);
        if (sz != v.sz)
            throw out_of_range("Different matrix sizes");
        else
            for (size_t i = 0; i < sz; i++)
                for (size_t j = 0; j < sz; j++)
                    for (size_t k = 0; k < sz; k++)
                        A.pMem[i][j] += pMem[i][k] * v.pMem[k][j];
        return(A);
    }

    size_t GetSize(void) const
    {
        return(sz);
    }

    TDynamicMatrix ReSizeM(size_t size)
    {
        if ((size == 0) || (size > MAX_VECTOR_SIZE))
            throw out_of_range("Invalid size");
        if (size == sz)
            return(*this);
        if (size > sz) {
            TDynamicMatrix A(size);
            for (size_t i = 0; i < sz; i++) {
                for (size_t j = 0; j < sz; j++) {
                    A[i][j] = (*this)[i][j];
                }
            }
            return(A);
        }
        else {
            TDynamicMatrix B(size);
            for (size_t i = 0; i < size; i++) {
                for (size_t j = 0; j < size; j++) {
                    B[i][j] = (*this)[i][j];
                }
            }
            return(B);
        }
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t j = 0; j < sz; j++)
            for (size_t i = 0; i < v.sz; i++)
                istr >> v.pMem[j][i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << '\n'; // требуется оператор<< для типа T
        return ostr;
    }
};

#endif

