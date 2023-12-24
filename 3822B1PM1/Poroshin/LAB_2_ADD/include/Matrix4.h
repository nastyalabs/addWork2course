#pragma once
#include <iostream>

using namespace std;

template<typename T>
class MATRIX
{
    size_t size;
    T* Value;
public:
    MATRIX() {
        size = 0;
        Value = nullptr;
    }
    MATRIX(size_t len) {
        if (len > MAX_MATRIX_SIZE)
            throw out_of_range("Matrix too large");
        size = len * len;
        Value = new T[size];
        for (int i = 0; i < size; i++) {
            Value[i] = 0;
        }
    }
    MATRIX(T* arr, size_t sz) //хранить матрицы по строкам
    {
        if (sz > MAX_MATRIX_SIZE * MAX_MATRIX_SIZE)
            throw out_of_range("Matrix too large");
        if (sz == 0) {
            size = 0;
            Value = nullptr;
        }
        else {
            size = sz;
            Value = new T[size];
            for (int i = 0; i < size; i++) {
                Value[i] = arr[i];
            }
        }
    }
    MATRIX(T* arr, size_t sz, char COLUMNS) //хранить матрицы по столбцам
    {
        if (sz > MAX_MATRIX_SIZE * MAX_MATRIX_SIZE)
            throw out_of_range("Matrix too large");
        if (sz == 0) {
            size = 0;
            Value = nullptr;
        }
        else {
            size = sz;
            Value = new T[size];
            int N = (int)sqrt(sz);
            T* mass = new T[sz];
            int j = 0;
            for (int t = 0; t < N; t++) {
                for (int i = t; i < N * N; i += N) {
                    mass[j] = arr[i];
                    j++;
                }
            }
            for (int i = 0; i < size; i++) {
                Value[i] = mass[i];
            }
        }
    }
    MATRIX(const MATRIX& v)
    {
        if (v.size != 0) {
            size = v.size;
            Value = new T[size];
            std::copy(v.Value, v.Value + size, Value);
        }
        else {
            size = 0;
            Value = nullptr;
        }
    }
    MATRIX(MATRIX&& v)
    {
        Value = nullptr;
        swap(v, *this);
    }
    ~MATRIX()
    {
        delete[] Value;
    }
    MATRIX& operator=(const MATRIX& v)
    {
        if (v.size != 0) {
            if (this == &v)
                return(*this);
            if (size != v.size) {
                T* tmp = new T[v.size];
                size = v.size;
                delete[] Value;
                Value = tmp;
            }
            std::copy(v.Value, v.Value + size, Value);
        }
        else {
            if (this == &v)
                return(*this);
            delete[] Value;
            size = 0;
            Value = nullptr;
        }
    }
    MATRIX& operator=(MATRIX&& v)
    {
        swap(v, *this);
        return(*this);
    }

    size_t GetSize() const { return size; }

    friend void swap(MATRIX& lhs, MATRIX& rhs)
    {
        std::swap(lhs.size, rhs.size);
        std::swap(lhs.Value, rhs.Value);
    }

    T* GetMatrix(void) const {
        T* arr = new T[size];
        for (int i = 0; i < size; i++) {
            arr[i] = Value[i];
        }
        return(arr);
    }

    MATRIX operator*(const MATRIX& v)
    {
        MATRIX B(0);
        if ((size == 0) || (v.size == 0))
            return(B);
        if (size != v.size)
            throw out_of_range("Different matrix sizes");
        else {
            MATRIX A(v.GetMatrix(), size, 'h');
            T* arr = new T[size];
            int N = (int)sqrt(size);
            int k = 0;
            for (int i = 0; i < size; i += N) {
                for (int j = 0; j < size; j += N) {
                    int first = i;
                    int first_A = j;
                    int last_A = j + N;
                    int sum = 0;
                    while (first_A < last_A) {
                        sum += A.Value[first_A] * Value[first];
                        first++;
                        first_A++;
                    }
                    arr[k] = sum;
                    k++;
                }
            }
            MATRIX C(arr, size);
            return(C);
        }
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, MATRIX& v)
    {
        for (int i = 0; i < v.size; i++) {
            cin >> v.Value[i];
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const MATRIX& v)
    {
        for (int i = 0; i < v.size; i++) {
            cout << v.Value[i] << " ";
            if ((i != 0) && ((i+1) % (int)sqrt(v.size) == 0)) {
                cout << '\n';
            }
        }
        return ostr;
    }
};