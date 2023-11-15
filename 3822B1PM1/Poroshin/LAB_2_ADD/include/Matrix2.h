#pragma once
#include <iostream>

using namespace std;

template<typename T>
class CRS_MATRIX
{
    size_t N;
    size_t size;
    T* Value;
    T* Column;
    T* Row_Index;
public:
    CRS_MATRIX(){
        N = 0;
        size = 0;
        Value = nullptr;
        Column = nullptr;
        Row_Index = nullptr;
    }
    CRS_MATRIX(size_t len) {
        if (len > MAX_MATRIX_SIZE)
            throw out_of_range("Matrix too large");
        N = 0;
        size = len;
        Value = new T[size];
        Column = new T[size];
        Row_Index = new T[size + 1];
        for (int i = 0; i < size + 1; i++) {
            Row_Index[i] = 0;
        }
        for (int i = 0; i < size; i++) {
            Value[i] = 0;
            Column[i] = 0;
        }
    }
    CRS_MATRIX(T* arr, size_t sz)
    {
        if (sz > MAX_MATRIX_SIZE*MAX_MATRIX_SIZE)
            throw out_of_range("Matrix too large");
        N = 0;
        for (size_t i = 0; i < sz; i++)
            if (arr[i] != 0)
                N++;
        if (N == 0) {
            size = 0;
            Value = nullptr;
            Column = nullptr;
            Row_Index = nullptr;
        }
        else {
            size = (int)sqrt(sz);
            Value = new T[N];
            Column = new T[N];
            Row_Index = new T[size + 1];
            Row_Index[0] = 0;
            for (int i = 0, j = 0, k = 0; i < sz; i++) {
                if (arr[i] != 0) {
                    Value[j] = arr[i];
                    Column[j] = i % size;
                    j++;
                }
                if (((i+1) % size == 0) && (i != 0)) {
                    Row_Index[k+1] = j;
                    k++;
                }
            }
        }
    }
    CRS_MATRIX(const CRS_MATRIX& v)
    {
        if (v.N != 0) {
            size = v.size;
            N = v.N;
            Value = new T[N];
            Column = new T[N];
            Row_Index = new T[size + 1];
            std::copy(v.Value, v.Value + N, Value);
            std::copy(v.Column, v.Column + N, Column);
            std::copy(v.Row_Index, v.Row_Index + size, Row_Index);
        }
        else {
            N = 0;
            size = 0;
            Value = nullptr;
            Column = nullptr;
            Row_Index = nullptr;
        }
    }
    CRS_MATRIX(CRS_MATRIX&& v) 
    {
        Value = nullptr;
        Column = nullptr;
        Row_Index = nullptr;
        swap(v, *this);
    }
    ~CRS_MATRIX()
    {
        delete[] Value;
        delete[] Column;
        delete[] Row_Index;
    }
    CRS_MATRIX& operator=(const CRS_MATRIX& v)
    {
        if (v.N != 0) {
            if (this == &v)
                return(*this);
            if (size != v.size) {
                T* tmp = new T[v.size];
                delete[] Row_Index;
                size = v.size;
                Row_Index = tmp;
            }
            if (N != v.N) {
                T* tmp1 = new T[v.N];
                T* tmp2 = new T[v.N];
                delete[] Value;
                delete[] Column;
                N = v.N;
                Value = tmp1;
                Column = tmp2;
            }
            std::copy(v.Value, v.Value + N, Value);
            std::copy(v.Column, v.Column + N, Column);
            std::copy(v.Row_Index, v.Row_Index + size + 1, Row_Index);
        }
        else {
            if (this == &v)
                return(*this);
            delete[] Value;
            delete[] Column;
            delete[] Row_Index;
            N = 0;
            size = 0;
            Value = nullptr;
            Column = nullptr;
            Row_Index = nullptr;
        }
    }
    CRS_MATRIX& operator=(CRS_MATRIX&& v) 
    {
        swap(v, *this);
        return(*this);
    }

    size_t GetSize() const  { return size; }
    size_t SizeN() const  { return N; }

    friend void swap(CRS_MATRIX& lhs, CRS_MATRIX& rhs) 
    {
        std::swap(lhs.size, rhs.size);
        std::swap(lhs.N, rhs.N);
        std::swap(lhs.Value, rhs.Value);
        std::swap(lhs.Column, rhs.Column);
        std::swap(lhs.Row_Index, rhs.Row_Index);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, CRS_MATRIX& v)
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
            delete[] v.Column;
            delete[] v.Row_Index;
            v.Value = nullptr;
            v.Column = nullptr;
            v.Row_Index = nullptr;
        }
        else {
            v.Value = new T[v.N];
            v.Column = new T[v.N];
            v.Row_Index = new T[v.size + 1];
            v.Row_Index[0] = 0;
            for (size_t i = 0, j = 0, k = 0; i < (v.size) * (v.size); i++) {
                if (arr[i] != 0) {
                    v.Value[j] = arr[i];
                    v.Column[j] = i % v.size;
                    j++;
                }
                if (((i + 1) % v.size == 0) && (i != 0)) {
                    v.Row_Index[k + 1] = j;
                    k++;
                }
            }
        }

        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const CRS_MATRIX& v)
    {
        if (v.N == 0) 
            cout << 0 << "\n";
        else
        for (size_t i = 0; i < (v.size) * (v.size); i += v.size) {
            int j = v.Row_Index[i / v.size];
            int k = v.Row_Index[(i / v.size) + 1];
            int l = 0;
            if (l != v.size) {
                if (j != k) {
                    while (j < k) {
                        if (l != v.Column[j]) {
                            cout << 0 << " ";
                            l++;
                        }
                        else {
                            cout << v.Value[j] << " ";
                            j++;
                            l++;
                        }
                    }
                }
                else {
                    for (size_t j = 0; j < v.size; j++) {
                        cout << 0 << " ";
                        l++;
                    }
                }
                while (l < v.size)
                {
                        cout << 0 << " ";
                        l++;
                }
                cout << "\n";
            }
        }
        return ostr;
    }






    /*
    //////////////////////////////////////////////////////////////////////////////////
    cout << "\n" << "-----------------------------" << "\n";
    cout << v.size << " " << v.N << endl;
    for (size_t i = 0; i < v.N; i++) {
        cout << v.Value[i] << " ";
    }
    cout << "\n";
    for (size_t i = 0; i < v.N; i++) {
        cout << v.Column[i] << " ";
    }
    cout << "\n";
    for (size_t i = 0; i < v.size + 1; i++) {
        cout << v.Row_Index[i] << " ";
    }
    cout << "\n" << "-----------------------------" << "\n";
    //////////////////////////////////////////////////////////////////////////////////
    */




};