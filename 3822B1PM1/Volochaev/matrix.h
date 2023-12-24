#pragma once
#include<iostream>
using namespace std;

//const int MaX_VECTOR_SIZE=100000000;
const int MAX_MATRIX_SIZE = 10000 * 10000;

template<class T>
class matrix
{
	size_t size;
	T* value;
public:
	matrix()
	{
		size = 0;
		value = nullptr;
	}

	~matrix() { delete[] value; }

	matrix(size_t sz)
	{
		if (sz >= MAX_MATRIX_SIZE) throw out_of_range("error");

		size = sz*sz;

		value = new T[size];
		memset(value, 0, size);
	}

	matrix(T* mas, size_t sz)
	{
		if (sz >= MAX_MATRIX_SIZE) throw out_of_range("error");
		if (sz == 0) matrix();
		else 
		{
			size = sz;
			value = new T[size];
			copy(mas, mas + size, value);
		}
	}

	matrix(T* mas, size_t sz, int z)
	{
		if (sz >= MAX_MATRIX_SIZE) throw out_of_range("error");
		if (sz == 0)
		{
			size = 0;
			value = nullptr;
		}
		else
		{
			size = sz;
			value = new T[size];
			int n = sqrt(sz);
			T* mass = new T[sz];
			int k = 0;
			for (int i = 0; i < n; ++i)
			{
				for (int j = i; j < n * n; j += n)
				{
					mass[k] = mas[j];
					k++;
				}
			}
			for (int i = 0; i < size; ++i) value[i] = mass[i];
		}
	}

	matrix(matrix&& m)
	{
		value = m.value;
		m.value = nullptr;
	}

	matrix operator*(const matrix& m)
	{
		matrix b;
		if ((size == 0) || (m.size == 0)) return b;
		if (size != m.size) throw out_of_range("error");
		else 
		{
			matrix a(m.value, size, 1);
			T* mas = new T[size];
			int n = sqrt(size);
			int k = 0;
			for (int i = 0; i < size; i += n)
			{
				for (int j = 0; j < size; j += n)
				{
					int first = i;
					int af = j;
					int al = j + n;
					int sum = 0;
					while (af < al)
					{
						sum += a.value[af] * value[first];
						++first;
						++af;
					}
					mas[k] = sum;
					++k;
				}
			}
			matrix c(mas, size);
			return c;
		}
	}
};