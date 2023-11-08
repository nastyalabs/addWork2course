#pragma once
#include "tmatrix.h"
#include <iostream>

template <typename T>
class TElementsVector
{
public:
	TElementsVector(size_t _size = 0);
	~TElementsVector() 
	{
		delete[] pMem;
	}
	TElementsVector(const TElementsVector& vector);
	TElementsVector(const TDynamicMatrix<T>& matrix);
	TElementsVector(TElementsVector<T>&& vector) noexcept
	{
		pMem = vector.pMem;
		size = vector.size;
		vector.pMem = nullptr;
	}
	TElementsVector& operator=(TElementsVector<T>&& vector) noexcept
	{
		std::swap(vector.pMem, pMem);
		size = vector.size;
		return *this;
	}
	T& at(size_t row, size_t column)
	{
		if (row >= size || column >= size) throw std::out_of_range("out of range");
		return pMem[row * size + column];
	}
	const T& at(size_t row, size_t column) const
	{
		if (row >= size || column >= size) throw std::out_of_range("out of range");
		return pMem[row * size + column];
	}
	friend std::ostream& operator<<(std::ostream& stream, const TElementsVector<T>& vector) {
		for (size_t i = 0; i < vector.size; i++)
		{
			size_t current = vector.size * i;
			for (size_t j = 0; j < vector.size; j++)
			{
				stream << std::setw(10) << vector.pMem[current + j];
			}
			stream << std::endl;
		}
		return stream;
	}
	TElementsVector& operator=(const TElementsVector& vector);
	bool operator==(const TElementsVector<T>& vector) const noexcept;
	bool operator!=(const TElementsVector<T>& vector) const noexcept
	{
		return !(*this == vector)
	}
	operator TDynamicMatrix<T>();

	// матрично-скалярные операции
	TElementsVector operator*(const T& val) const;

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v) const;

	// матрично-матричные операции
	TElementsVector operator+(const TElementsVector& m) const;
	TElementsVector operator-(const TElementsVector& m) const;
	TElementsVector operator*(const TElementsVector& m) const;

private:
	T* pMem;
	size_t size;
};

template<typename T>
inline TElementsVector<T>::TElementsVector(size_t _size)
{
	if (size == 0) {
		pMem = nullptr;
		size = 0;
	}
	else
	{
		size = _size;
		pMem = new T[size * size]();
	}
}

template<typename T>
inline TElementsVector<T>::TElementsVector(const TElementsVector& vector)
{
	if (vector.size == 0) {
		pMem = nullptr;
		size = 0;
	}
	else
	{
		size = vector.size;
		pMem = new T[size * size];
		std::copy(vector.pMem, vector.pMem + size * size, pMem);
	}
}

template<typename T>
inline TElementsVector<T>::TElementsVector(const TDynamicMatrix<T>& matrix)
{
	size = matrix.size();
	pMem = new T[size * size];
	for (size_t i = 0; i < size; i++)
	{
		size_t current = i * size;
		for (size_t j = 0; j < size; j++)
		{
			pMem[current + j] = matrix[i][j];
		}
	}
}

template<typename T>
inline TElementsVector<T>& TElementsVector<T>::operator=(const TElementsVector<T>& vector)
{
	if (vector.size == 0) {
		delete[] pMem;
		pMem = nullptr;
		size = 0;
	}
	else
	{
		if (vector.pMem != pMem) {
			if (vector.size != size) {
				T* tmp = new T[size];
				delete[] pMem;
				pMem = tmp;
			}
			std::copy(vector.pMem, vector.pMem + (size * size), pMem);
		}
	}
	return *this;
}

template<typename T>
inline bool TElementsVector<T>::operator==(const TElementsVector<T>& vector) const noexcept
{
	if (size != vector.size) return false;
	size_t length = size * size;
	for (size_t i = 0; i < length; i++)
	{
		if (pMem[i] != vector.pMem[i]) return false;
	}
	return true;
}

template<typename T>
inline TElementsVector<T>::operator TDynamicMatrix<T>()
{
	TDynamicMatrix<T> result(size);
	for (size_t i = 0; i < size; i++)
	{
		size_t current = i * size;
		for (size_t j = 0; j < size; j++)
		{
			result[i][j] = pMem[current + j];
		}
	}
	return result;
}

template<typename T>
inline TElementsVector<T> TElementsVector<T>::operator*(const T& val) const
{
	TElementsVector<T> result(size);
	size_t sz = size * size;
	for (size_t i = 0; i < sz; i++)
	{
		result.pMem[i] = pMem[i] * val;
	}
	return result;
}

template<typename T>
inline TDynamicVector<T> TElementsVector<T>::operator*(const TDynamicVector<T>& v) const
{
	if (size != v.size()) throw std::invalid_argument("You can not multiply matrix and vector with not equal sizes");
	TDynamicVector<T> res(size);
	for (size_t i = 0; i < size; i++)
	{
		T sum = 0;
		size_t current = i * size;
		for (size_t j = 0; j < size; j++)
		{
			sum += pMem[current + j] * v[j];
		}
		res[i] = sum;
	}
	return res;
}

template<typename T>
inline TElementsVector<T> TElementsVector<T>::operator+(const TElementsVector& m) const
{
	if (size != m.size) throw std::invalid_argument("You can not sum matrix with not equal sizes");
	TElementsVector<T> res(size);
	size_t length = size * size;
	for (size_t i = 0; i < length; i++)
	{
		res.pMem[i] = pMem[i] + m.pMem[i];
	}
	return res;
}

template<typename T>
inline TElementsVector<T> TElementsVector<T>::operator-(const TElementsVector& m) const
{
	if (size != m.size) throw std::invalid_argument("You can not sum matrix with not equal sizes");
	TElementsVector<T> res(size);
	size_t length = size * size;
	for (size_t i = 0; i < length; i++)
	{
		res.pMem[i] = pMem[i] - m.pMem[i];
	}
	return res;
}

template<typename T>
inline TElementsVector<T> TElementsVector<T>::operator*(const TElementsVector& m) const
{
	if (size != m.size) throw std::invalid_argument("You can not sum matrix with not equal sizes");
	TElementsVector<T> res(size);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			T sum = 0;
			for (size_t k = 0; k < size; k++)
			{
				sum += pMem[i * size + k] * m.pMem[k * size + j];
			}
			res.pMem[i * size + j] = sum;
		}
	}
	return res;
}
