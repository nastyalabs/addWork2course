#pragma once

#include<iostream>
using namespace std;

//const int MAX_VECTOR_SIZE = 100000000;
//const int MAX_MATRIX_SIZE = 10000 * 10000;

template<class T>
class xy
{
    size_t size;
    size_t n;
    T* x;
    T* y;
    T* value;
public:

    xy()
    {
        n=0;
        size=0;
        x=nullptr;
        y=nullptr;
        value=nullptr;
    }

    xy(const size_t sz)
    {
        if (sz >= MAX_MATRIX_SIZE) throw out_of_range("error");

        if (sz == 0) xy();
        else
        {
            n = 0;
            size = sz;
            x = new T[size * size];
            y = new T[size * size];
            value = new T[size * size];
            memset(x, 0, size * size);
            memset(y, 0, size * size);
            memset(value, 0, size * size);
        }
    }

    xy(T* mas, size_t sz)
    {
        if (sz >= MAX_MATRIX_SIZE) throw out_of_range("error");

        if (sz == 0) xy();
        else
        {
            n = 0;
            for (int i = 0; i < sz; ++i) n += mas[i] != 0;

            if (!n) xy();
            else
            {
                size = sqrt(sz);
                value = new T[n];
                x = new T[n];
                y = new T[n];
                int j = 0;
                for (int i = 0; i < sz; ++i) if (mas[i]) value[j] = mas[i], x[j] = i / size, y[j] = i % size, ++j;
            }
        }
    }

    xy(T* mas, size_t sz, int t)
    {
        if (sz > MAX_MATRIX_SIZE) throw out_of_range("error");
        n = 0;
        for (size_t i = 0; i < sz; ++i) n+=mas[i]!=0;
        if (n == 0) xy();
            
        else
        {
            size=sqrt(sz);
            T* mas=new T[sz];
            int k = 0;
            for (int i = 0; i < size; ++i)
            {
                for (int j = i; j < size * size; j += size)
                {
                    mas[k] = mas[j];
                    k++;
                }
            }
            x = new T[n];
            y = new T[n];
            value = new T[n];
            k = 0;
            for (int i = 0; i < sz; ++i)
            {
                if (mas[i] != 0)
                {
                    value[k] = mas[i];
                    x[k] = i / size;
                    y[k] = i % size;
                    ++k;
                }
            }
        }
    }

    xy(const xy& m)
    {
        if (m.n)
        {
            size = m.size;
            n = m.n;
            x = new T[n];
            y = new T[n];
            value = new T[n];
            copy(m.value, m.value + n, value);
            copy(m.x, m.x + n, x);
            copy(m.y, m.y + n, y);
        }
        else xy();
    }

    xy(xy&& m)
    {
        n = m.n;
        size = m.size;
        x = m.x;
        y = m.y;
        value = m.value;
        m.n = 0;
        m.size = 0;
        m.x = nullptr;
        m.y = nullptr;
        m.value = nullptr;
    }
 
    ~xy()
    {
        delete[] x;
        delete[] y;
        delete[] value;
    }

    size_t size_() const { return size; }
    size_t n_() const { return n; }

    xy operator=(const xy& m)
    {
        if (this == &m) return *this;

        if (m.n)
        {
            if (n != m.n) 
            {
                delete[] x;
                delete[] y;
                delete[] value;
                x = new T[m.n];
                y = new T[m.n];
                value = new T[m.n];
                n = m.n;
            }
            size = m.size;
            copy(m.x, m.x + n, x);
            copy(m.y, m.y + n, y);
            copy(m.value, m.value + n, value);
        }
        else
        {
            if(x!=nullptr) delete[] x;
            if (y != nullptr)delete[] y;
            if (value != nullptr)delete[] value;
            xy();
        }
    }

    xy operator*(const xy& m)
    {
        xy b;
        if ((n == 0) || (m.n == 0)) return b;

        if (size != m.size) throw out_of_range("error");
        else
        {

            T* mas1 = new T[size * size];
            for (int i = 0; i < size * size; ++i) mas1[i] = 0;
            if (n)
            {
                int id1 = 0;
                int id = 0;
                int j = 0;
                for (size_t i = 0; i < size * size; i += size)
                {
                    if (x[id] > j)
                    {
                        int k = x[id];
                        int f = j;
                        while (k != f)
                        {
                            int l = 0;
                            while (l < size)
                            {
                                id1++;
                                l++;
                            }
                            k--;
                            j++;
                        }
                    }
                    else
                    {
                        int l = 0;
                        int k = id;
                        while (l < size) {
                            if ((l == y[k]) && (j == x[k]))
                            {
                                mas1[id1] = value[k];
                                id1++;
                                l++;
                                k++;
                            }
                            else
                            {
                                id1++;
                                l++;
                            }
                        }
                        id = k;
                        j++;
                    }
                }
            }

            size_t  sz = size * size;;
            xy a(mas1, sz, (int)1);
            delete[] mas1;
            T* mas = new T[size * size];
            for (int i = 0; i < size * size; ++i) mas[i] = 0;
            int id2 = 0;
            int id = 0;
            for (int i = 0; i < size; ++i) 
            {
                if (x[id2] > i) {id += size;continue;}

                int id1 = 0;
                int g = id2;
                for (int j = 0; j < size; ++j) 
                {
                    if (a.x[id1] > j){++id;continue;}

                    int sum = 0;
                    int l = 0;
                    int k = id1;
                    int f = id2;
                    while (l < size)
                    {
                        if ((l == y[f]) && (l == a.y[k]) && (x[id2] == x[f]) && (a.x[id1] == a.x[k])) sum += value[f] * a.value[k],++l, ++k, ++f;
                        else
                        {
                            if ((l == y[f]) && (x[id2] == x[f])) ++f;
                            if ((l == a.y[k]) && (a.x[id1] == a.x[k])) ++k;
                            ++l;
                        }
                    }
                    if (k > id1) id1 = k;
                    else ++id1;
                    mas[id] = sum;
                    ++id;
                    g = max(g, f);
                }
                if (g > id2) id2 = g;
                else ++id2;
            }
            xy c(mas, size * size);
            return c;
        }
    }
};