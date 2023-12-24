#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE=100000000;
//const int MAX_MATRIX_SIZE= 10000 * 10000;

typedef long double ld;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<class T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector()
    {
        sz = 0;
        pMem = nullptr;
    }

    TDynamicVector(size_t size)
    {
        sz = size;
        if (sz == 0) throw out_of_range("Vector size should be greater than zero");
        if (sz >= MAX_VECTOR_SIZE) throw out_of_range("is so big size");
        pMem = new T[sz];// {}; // У типа T д.б. констуктор по умолчанию
    }

    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(size_t size, T x)
    {
        if (size == 0) throw out_of_range("Vector size should be greater than zero");
        if (size > MAX_VECTOR_SIZE) throw out_of_range("is so big size");
        sz = size;
        pMem = new T[sz]();
        for (size_t i = 0; i < sz; ++i) pMem[i] = x;
    }

    TDynamicVector(const TDynamicVector<T>& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (size_t i = 0; i < sz; ++i) pMem[i] = v.pMem[i];
    }

    TDynamicVector(TDynamicVector<T>&& v) noexcept
    {
        sz = v.sz;
        pMem = v.pMem;
        v.pMem = nullptr;
        v.sz = 0;
    }

    ~TDynamicVector() { delete[] pMem; sz = 0; }

    TDynamicVector& operator=(const TDynamicVector<T>& v)
    {
        if (*this == v) return *this;
        sz = v.sz;
        delete[] pMem;
        pMem = new T[sz];
        for (size_t i = 0; i < sz; ++i) pMem[i] = v.pMem[i];
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector<T>&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind) { return at(ind); }
    const T& operator[](size_t ind) const { return at(ind); }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz || ind >= sz) throw out_of_range("index should be less than length of erray");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz || ind < 0)throw out_of_range("index should be less than length of erray");
        return pMem[ind];
    }
    // сравнение
    bool operator==(const TDynamicVector<T>& v) const noexcept
    {
        if (v.sz == sz)
        {
            for (size_t i = 0; i < sz; ++i) if (v.pMem[i] != pMem[i]) return false;
            return true;
        }
        else return false;
    }
    bool operator!=(const TDynamicVector& v) const noexcept { return !(*this == v); }
    // скалярные операции
    TDynamicVector operator+(T val) noexcept
    {
        TDynamicVector<T> ans(sz, 0);
        for (size_t i = 0; i < sz; ++i) ans.pMem[i] = pMem[i] + val;

        return ans;
    }
    TDynamicVector operator-(T val) noexcept { return operator+(-val); }
    TDynamicVector operator*(T val) noexcept
    {
        TDynamicVector<T> ans(sz);

        for (size_t i = 0; i < sz; ++i) ans.pMem[i] = pMem[i] * val;
        return ans;
    }
    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "vectors of different spaces";
        TDynamicVector<T> ans(sz);

        for (size_t i = 0; i < sz; ++i) ans.pMem[i] = pMem[i] + v.pMem[i];
        return ans;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "vectors of different spaces";
        TDynamicVector<T> ans(sz);
        for (size_t i = 0; i < sz; ++i) ans.pMem[i] = pMem[i] - v.pMem[i];
        return ans;
    }

    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "vectors of different spaces";
        ld ans = 0;
        for (size_t i = 0; i < sz; ++i) ans += pMem[i] * v.pMem[i];
        return ans;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
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

template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz >= MAX_MATRIX_SIZE) throw out_of_range("is so big size");
        for (size_t i = 0; i < sz; i++) pMem[i] = TDynamicVector<T>(sz, 0);
    }

    size_t size() noexcept { return sz; }

    void resize(size_t size)
    {
        if (size >= MAX_MATRIX_SIZE) throw out_of_range("is so big size");
        TDynamicMatrix<T> ans(size);
        *this = ans;
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; ++i) if (pMem[i] != m.pMem[i]) return false;
        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix<T> ans(sz);
        for (size_t i = 0; i < sz; ++i) ans[i] = pMem[i] * val;
        return ans;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        T ans = 0;
        if (sz != v.sz) throw out_of_range("isn't equal size");
        for (size_t i = 0; i < sz; ++i) ans += pMem[i] * v.pMem[i];
        return ans;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw out_of_range("isn't equal size");
        TDynamicMatrix<T> ans(sz);
        for (size_t i = 0; i < sz; ++i) ans[i] = pMem[i] + m[i];
        return ans;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw out_of_range("isn't equal size");
        TDynamicMatrix<T> ans(sz);
        for (size_t i = 0; i < sz; ++i) ans[i] = pMem[i] - m[i];
        return ans;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw out_of_range("isn't equal size");
        TDynamicMatrix<T> ans(sz);

        for (size_t i = 0; i < sz; ++i)
        {
            for (size_t j = 0; j < sz; ++j)
            {
                T ans_ = 0;
                for (size_t k = 0; k < sz; ++k)
                    ans_ += pMem[i][k] * m.pMem[k][j];
                ans.pMem[i][j] = ans_;
            }
        }


        return ans;
    }

    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i)
        {
            for (size_t j = 0; j < v.sz; ++j)
            {
                cin >> v[i][j];
            }
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i)
        {
            for (size_t j = 0; j < v.sz; ++j)
            {
                cout << v[i][j];
            }
        }
        return ostr;
    }
};

#endif