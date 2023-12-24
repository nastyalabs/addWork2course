#pragma once
#include <iostream>

using namespace std;

template<typename T>
class XY_MATRIX
{
    size_t size;
    size_t N;
    T* massX;
    T* massY;
    T* Value;

public:
    XY_MATRIX() {
        N = 0;
        size = 0;
        Value = nullptr;
        massY = nullptr;
        massX = nullptr;
    }
    XY_MATRIX(size_t len) {
        if (len > MAX_MATRIX_SIZE)
            throw out_of_range("Matrix too large");
        N = 0;
        size = len;
        Value = new T[size * size];
        massX = new T[size * size];
        massY = new T[size * size];
        for (int i = 0; i < size * size; i++) {
            Value[i] = 0;
            massY[i] = 0;
            massX[i] = 0;
        }
    }
    XY_MATRIX(T* arr, size_t sz) //хранить матрицы по строчкам
    {
        if (sz > MAX_MATRIX_SIZE * MAX_MATRIX_SIZE)
            throw out_of_range("Matrix too large");
        N = 0;
        for (size_t i = 0; i < sz; i++)
            if (arr[i] != 0)
                N++;
        if (N == 0) {
            size = 0;
            Value = nullptr;
            massY = nullptr;
            massX = nullptr;
        }
        else {
            size = (int)sqrt(sz);
            Value = new T[N];
            massX = new T[N];
            massY = new T[N];
            for (int i = 0, j = 0;  i < sz; i++) {
                if (arr[i] != 0) {
                    Value[j] = arr[i];
                    massX[j] = i / size;
                    massY[j] = i % size;
                    j++;
                }
            }
        }
    }
    XY_MATRIX(T* arr, size_t sz, char COLUMNS) //хранить матрицы по столбцам
    {
        if (sz > MAX_MATRIX_SIZE * MAX_MATRIX_SIZE)
            throw out_of_range("Matrix too large");
        N = 0;
        for (size_t i = 0; i < sz; i++)
            if (arr[i] != 0)
                N++;
        if (N == 0) {
            size = 0;
            Value = nullptr;
            massY = nullptr;
            massX = nullptr;
        }
        else {
            size = (int)sqrt(sz);
            T* mass = new T[sz];
            int j = 0;
            for (int t = 0; t < size; t++) {
                for (int i = t; i < size * size; i += size) {
                    mass[j] = arr[i];
                    j++;
                }
            }
            Value = new T[N];
            massX = new T[N];
            massY = new T[N];
            for (int i = 0, j = 0; i < sz; i++) {
                if (mass[i] != 0) {
                    Value[j] = mass[i];
                    massX[j] = i / size;
                    massY[j] = i % size;
                    j++;
                }
            }
        }
    }
    XY_MATRIX(const XY_MATRIX& v)
    {
        if (v.N != 0) {
            size = v.size;
            N = v.N;
            Value = new T[N];
            massX = new T[N];
            massY = new T[N];
            std::copy(v.Value, v.Value + N, Value);
            std::copy(v.massX, v.massX + N, massX);
            std::copy(v.massY, v.massY + N, massY);
        }
        else {
            N = 0;
            size = 0;
            Value = nullptr;
            massY = nullptr;
            massX = nullptr;
        }
    }
    XY_MATRIX(XY_MATRIX&& v)
    {
        Value = nullptr;
        massY = nullptr;
        massX = nullptr;
        swap(v, *this);
    }
    ~XY_MATRIX()
    {
        delete[] Value;
        delete[] massX;
        delete[] massY;
    }
    friend void swap(XY_MATRIX& lhs, XY_MATRIX& rhs)
    {
        std::swap(lhs.size, rhs.size);
        std::swap(lhs.N, rhs.N);
        std::swap(lhs.Value, rhs.Value);
        std::swap(lhs.massX, rhs.massX);
        std::swap(lhs.massY, rhs.massY);
    }
    size_t GetSize() const { return size; }
    size_t SizeN() const { return N; }
    XY_MATRIX& operator=(const XY_MATRIX& v)
    {
        if (v.N != 0) {
            if (this == &v)
                return(*this);
            if (N != v.N) {
                T* tmp1 = new T[v.N];
                T* tmp2 = new T[v.N];
                T* tmp3 = new T[v.N];
                delete[] Value;
                delete[] massY;
                delete[] massX;
                N = v.N;
                Value = tmp1;
                massX = tmp2;
                massY = tmp3;
            }
            size = v.size;
            std::copy(v.Value, v.Value + N, Value);
            std::copy(v.massX, v.massX + N, massX);
            std::copy(v.massY, v.massY + N, massY);
        }
        else {
            if (this == &v)
                return(*this);
            delete[] Value;
            delete[] massY;
            delete[] massX;
            N = 0;
            size = 0;
            Value = nullptr;
            massY = nullptr;
            massX = nullptr;
        }
    }
    XY_MATRIX& operator=(XY_MATRIX&& v)
    {
        swap(v, *this);
        return(*this);
    }
    friend istream& operator>>(istream& istr, XY_MATRIX& v)
    {
        T* arr = new T[(v.size) * (v.size)];
        for (size_t i = 0; i < (v.size) * (v.size); i++)
            istr >> arr[i]; // требуется оператор>> для типа T
        v.N = 0;
        for (size_t i = 0; i < (v.size) * (v.size); i++)
            if (arr[i] != 0)
                v.N++;
        if (v.N == 0) {
            v.size = 0;
            delete[] v.Value;
            delete[] v.massY;
            delete[] v.massX;
            v.Value = nullptr;
            v.massY = nullptr;
            v.massX = nullptr;
        }
        else {
            v.Value = new T[v.N];
            v.massX = new T[v.N];
            v.massY = new T[v.N];
            for (int i = 0, j = 0;  i < v.size * v.size; i++) {
                if (arr[i] != 0) {
                    v.Value[j] = arr[i];
                    v.massX[j] = i / v.size;
                    v.massY[j] = i % v.size;
                    j++;
                }
            }
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const XY_MATRIX& v)
    {
        if (v.N == 0)
            cout << 0 << "\n";
        else {
            int id = 0; //индекс для строки в massX
            int j = 0; //индекс для строки в матрице
            for (size_t i = 0; i < (v.size) * (v.size); i += v.size) {
                if (v.massX[id] > j) {
                    int k = v.massX[id];
                    int f = j;
                    while (k != f) {
                        int l = 0;
                        while (l < v.size) {
                            cout << 0 << " ";
                            l++;
                        }
                        cout << "\n";
                        k--;
                    j++;
                    }
                }
                else {
                    int l = 0;
                    int k = id;
                    while (l < v.size) {
                        if ((l == v.massY[k])&&(j == v.massX[k])) {
                            cout << v.Value[k] << " ";
                            l++;
                            k++;
                        }
                        else {
                            cout << 0 << " ";
                            l++;
                        }
                    }
                    cout << "\n";
                    id = k;
                    j++;
                }
            }  
        }
        return ostr;
    }
    T* GetMatrix(void) const
    {
        T* arr = new T[(size) * (size)];
        for (int i = 0; i < (size) * (size); i++)
            arr[i] = 0;
        if (N == 0)
            return(arr);
        else {
            int iter = 0; //переменная для обхода массива
            int id = 0; //индекс для строки в massX
            int j = 0; //индекс для строки в матрице
            for (size_t i = 0; i < (size) * (size); i += size) {
                if (massX[id] > j) {
                    int k = massX[id];
                    int f = j;
                    while (k != f) {
                        int l = 0;
                        while (l < size) {
                            iter++;
                            l++;
                        }
                        k--;
                        j++;
                    }
                }
                else {
                    int l = 0;
                    int k = id;
                    while (l < size) {
                        if ((l == massY[k]) && (j == massX[k])) {
                            arr[iter] = Value[k];
                            iter++;
                            l++;
                            k++;
                        }
                        else {
                            iter++;
                            l++;
                        }
                    }
                    id = k;
                    j++;
                }
            }
        }
        return(arr);
    }
    XY_MATRIX operator*(const XY_MATRIX& v)
    {
        XY_MATRIX B(0);
        if ((N == 0) || (v.N == 0))
            return(B);
        if (size != v.size)
            throw out_of_range("Different matrix sizes");
        else {
            XY_MATRIX A(v.GetMatrix(), size * size, 'h');
            T* arr = new T[(size) * (size)];
            for (int i = 0; i < (size) * (size); i++)
                arr[i] = 0;
            int id2 = 0;
            int iter = 0;
            for (int i = 0; i < size; i++) {
                if (massX[id2] > i) {
                    iter += size;
                    continue;
                }
                int id1 = 0;
                int g = id2;
                for (int j = 0; j < size; j++) {
                    if (A.massX[id1] > j) {
                        iter++;
                        continue;
                    }
                    int sum = 0;
                    int l = 0;
                    int k = id1;
                    int f = id2;
                    while (l < size) {
                        if ((l == massY[f]) && (l == A.massY[k]) && (massX[id2] == massX[f]) && (A.massX[id1] == A.massX[k])) {
                            sum += Value[f] * A.Value[k];
                            l++;
                            k++;
                            f++;
                        }
                        else {
                            if ((l == massY[f]) && (massX[id2] == massX[f]))
                                f++;
                            if ((l == A.massY[k]) && (A.massX[id1] == A.massX[k]))
                                k++;
                            l++;
                        }
                    }
                    if (k > id1)
                        id1 = k;
                    else
                        id1++;
                    arr[iter] = sum;
                    iter++;
                    g = max(g, f);
                }
                if (g > id2)
                    id2 = g;
                else
                    id2++;
            }
        XY_MATRIX C(arr, size * size);
        return(C);
        }
    }
};