#pragma once

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000 * 10000;

template<class T>
class crs
{
    size_t n;
    size_t size;
    T* value, column, id;
public:

    crs()
    {
        n = 0;
        size = 0;
        value = column = id = nullptr;
    }

    crs(size_t sz)
    {
        if (sz >= MAX_MATRIX_SIZE) throw out_of_range("error");

        if (sz == 0) CRS();
        else
        {
            n = 0;
            size = sz;
            value = new T[size];
            column = new T[size];
            id = new T[size + 1];
            memset(value, 0, size);
            memset(column, 0, size);
            memset(id, 0, size + 1);
        }
    }

    crs(T* mas, size_t sz)
    {
        if (sz >= MAX_MATRIX_SIZE) throw out_of_range("error");

        n = 0;
        for (int i = 0; i < sz; ++i) n += mas[i] != 0;
        if (!n) CRS();
        else
        {
            size = sqrt(sz);
            value = new T[n];
            column = new T[n];
            id = new T[size + 1];
            id[0] = 0;
            int j = 0, k = 0;
            for (int i = 0; i < sz; ++i)
            {
                if (mas[i] != 0) value[j] = mas[i], column[j] = i % size, ++j;
                if (((i + 1) % size == 0) && (i != 0)) id[k + 1] = j, ++k;
            }
        }
    }

    crs(const crs& m)
    {
        if (m.N != 0)
        {
            size = m.size;
            n = m.n;
            value = new T[n];
            column = new T[n];
            id = new T[size + 1];
            copy(m.Value, m.value + n, value);
            copy(m.Column, m.column + n, column);
            copy(m.id, m.id + size + 1, id);
        }
        else CRS();
    }

    crs(crs&& m)
    {
        crs();
        swap(m, *this);
    }

    ~crs()
    {
        delete[] value;
        delete[] column;
        delete[] id;
    }

    crs& operator=(const crs& m)
    {
        if (m.N != 0)
        {
            if (this == &m) return *this;
            if (size != m.size)
            {
                delete[] id;
                size = m.size;
                id = new T[size];
            }
            if (n != m.n)
            {
                delete[] value;
                delete[] column;
                value = new T[m.N];
                column = new T[m.N];
                n = m.n;
            }
            copy(m.value, m.value + n, value);
            copy(m.column, m.column + n, column);
            copy(m.id, m.id + size + 1, id);
        }
        else
        {
            if (this == &m) return *this;
            ~crs();
            crs();
        }
    }

    crs& operator=(CRS&& m)
    {
        swap(m, *this);
        return *this;
    }

    size_t size_() const { return size; }
    size_t n_() const { return n; }
};