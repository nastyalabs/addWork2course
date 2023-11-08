#pragma once
#include "tmatrix.h"
#include "tvector.h"
#include <iostream>
template <typename T>
class TCompressedSparseRow
{
public:
	operator TDynamicMatrix<T>() const;
	TCompressedSparseRow(size_t size);
	TCompressedSparseRow() : TCompressedSparseRow(0) {}
	TCompressedSparseRow(const TDynamicMatrix<T>& matrix);
	~TCompressedSparseRow();
	//compare
	bool operator== (const TCompressedSparseRow& CSR) const noexcept;
	bool operator!= (const TCompressedSparseRow& CSR) const noexcept;
	//matrix to matrix operations
	TCompressedSparseRow operator+ (const TCompressedSparseRow& CSR) const;
	TCompressedSparseRow operator* (const TCompressedSparseRow& CSR) const;
	TCompressedSparseRow operator- (const TCompressedSparseRow& CSR) const;

	//matrix operations
	TCompressedSparseRow operator-() const noexcept;
	friend std::ostream& operator<< (std::ostream& stream, const TCompressedSparseRow& CSR) 
	{
		stream << CSR.values << std::endl << CSR.columns << std::endl << CSR.rows;
		return stream;
	}
	TCompressedSparseRow transpose() const noexcept;
	const T& get(size_t row, size_t column) const;
	void set(const T& element, size_t row, size_t column);
	size_t get_row(size_t index) const {
		for (size_t i = 1; i < rows.getSize(); i++)
		{
			for (size_t j = rows[i-1]; j < rows[i]; j++)
			{
				if (j == index)
					return i - 1;
			}
		}
		throw std::out_of_range("index is not exist");
	}
	//matrix to vector operations
	TDynamicVector<T> operator* (const TDynamicVector<T>& vector) const;
	TCompressedSparseRow<T> operator- (const TDynamicVector<T>& vector) const;
	TCompressedSparseRow operator* (const T& CSR) const;
private:
	size_t size;
	Vector<T> values;
	Vector<size_t> columns;
	Vector<size_t> rows;
};

template<typename T>
inline TCompressedSparseRow<T>::operator TDynamicMatrix<T>() const
{
	TDynamicMatrix<T> matrix(size);
	size_t size = rows.getSize();
	for (size_t i = 1; i < size; i++)
	{
		for (size_t j = rows[i-1]; j < rows[i]; j++)
		{
			matrix[i-1][columns[j]] = values[j];
		}
	}
	return matrix;
}
template <typename T>
TCompressedSparseRow<T>::TCompressedSparseRow(size_t _size) : values(), columns(), size(_size)
{
	rows = Vector<size_t>(2 * _size, 0);
}
template<typename T>
inline TCompressedSparseRow<T>::TCompressedSparseRow(const TDynamicMatrix<T>& matrix)
{
	size = matrix.size();
	for (size_t i = 0; i < matrix.size(); i++)
	{
		bool is_start = true;
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] != 0) {
				if (is_start)
				{
					rows.push_back(values.getSize());
					is_start = false;
				}
				values.push_back(matrix[i][j]);
				columns.push_back(j);
			}
		}
		if (is_start) {
			rows.push_back(values.getSize());
		}
	}
	rows.push_back(values.getSize());
}
template <typename T>
TCompressedSparseRow<T>::~TCompressedSparseRow()
{
}
template<typename T>
inline bool TCompressedSparseRow<T>::operator==(const TCompressedSparseRow& CSR) const noexcept
{
	if (size != CSR.size) return false;
	if (values.getSize() != CSR.values.getSize()) return false;
	for (size_t i = 0; i < values.getSize(); i++)
	{
		if (values[i] != CSR.values[i])
			return false;
	}
	if (rows.getSize() != CSR.rows.getSize()) return false;
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		if (rows[i] != CSR.rows[i])
			return false;
	}
	if (columns.getSize() != CSR.columns.getSize()) return false;
	for (size_t i = 0; i < columns.getSize(); i++)
	{
		if (columns[i] != CSR.columns[i])
			return false;
	}
	return true;
}
template<typename T>
inline bool TCompressedSparseRow<T>::operator!=(const TCompressedSparseRow& CSR) const noexcept
{
	return !(*this == CSR)
}

template <typename T>
TCompressedSparseRow<T> TCompressedSparseRow<T>::transpose() const noexcept
{
	TCompressedSparseRow CSR_transpose(size);
	CSR_transpose.rows.clear();
	CSR_transpose.rows.SetCopacity(rows.getSize());
	CSR_transpose.columns.SetCopacity(columns.getSize());
	CSR_transpose.values.SetCopacity(values.getSize());
	size_t columns_size = columns.getSize();
	size_t rows_size = rows.getSize();
	for (size_t i = 0; i < size; i++)
	{
		bool is_first = true;
		for (size_t j = 1; j < rows_size; j++)
		{
			for (size_t k = rows[j-1]; k < rows[j]; k++)
			{
				if (columns[k] == i) {
					if (is_first) {
						CSR_transpose.rows.push_back(CSR_transpose.values.getSize());
						is_first = false;
					}
					CSR_transpose.columns.push_back(j - 1);
					CSR_transpose.values.push_back(values[k]);
				}
			}
		}
		if (is_first) {
			CSR_transpose.rows.push_back(CSR_transpose.values.getSize());
		}
	}
	CSR_transpose.rows.push_back(CSR_transpose.values.getSize());
	return CSR_transpose;
}
template<typename T>
inline const T& TCompressedSparseRow<T>::get(size_t row, size_t column) const
{
	if (column >= size && row >= size) throw std::out_of_range("you can not get out of range element");
	for (size_t i = rows[row]; i < rows[row+1]; i++)
	{
		if (columns[i] == column)
			return values[i];
	}
	return (T)0;
}
template<typename T>
inline void TCompressedSparseRow<T>::set(const T& element, size_t row, size_t column)
{
	if (column >= size && row >= size) throw std::out_of_range("you can not get out of range element");
	for (size_t i = rows[row]; i < rows[row + 1]; i++)
	{
		if (columns[i] == column) {
			if (element != 0) 
			{
				values[i] = element;
			}
			else
			{
				values.erase(i);
				columns.erase(i);
				for (size_t j = rows[row] + 1; j < rows.getSize(); j++)
				{
					rows[j]--;
				}
			}
			return;
		}
	}
	values.insert(rows[row], element);
	columns.insert(rows[row], column);
	for (size_t j = rows[row] + 1; j < rows.getSize(); j++)
	{
		rows[j]++;
	}
	return;
}

template<typename T>
TDynamicVector<T> TCompressedSparseRow<T>::operator* (const TDynamicVector<T>& vector) const
{
	TDynamicVector<T> result(size);
	for (size_t i = 1; i < rows.getSize(); i++)
	{
		T sum = {};
		for (size_t j = rows[i-1]; j < rows[i]; j++)
		{
			sum += values[j] * vector[columns[j]];
		}
		result[i - 1] = sum;
	}
	return result;
}
template<typename T>
inline TCompressedSparseRow<T> TCompressedSparseRow<T>::operator-(const TDynamicVector<T>& vector) const
{
	return *this + (-vector);
}
template<typename T>
inline TCompressedSparseRow<T> TCompressedSparseRow<T>::operator*(const T& scalar) const
{
	TCompressedSparseRow result(*this);
	for (size_t i = 0; i < result.values.getSize(); i++)
	{
		result.values[i] *= scalar;
	}
	return result;
}
template <typename T>
TCompressedSparseRow<T> TCompressedSparseRow<T>::operator+ (const TCompressedSparseRow& CSR) const
{
	if (size != CSR.size) throw std::invalid_argument("sizes of matrix should be equal");
	TCompressedSparseRow result(size);
	result.rows.clear();
	size_t this_row_num = 0;
	size_t CSR_row_num = 0;
	size_t k = 0;
	size_t j = 0;
	Vector<size_t> result_rows;
	while (k < values.getSize() && j < CSR.values.getSize())
	{
		this_row_num = get_row(k);
		CSR_row_num = CSR.get_row(j);
		if (this_row_num == CSR_row_num) 
		{
			if (columns[k] < CSR.columns[j]) 
			{
				result.values.push_back(values[k]);
				result.columns.push_back(columns[k]);
				result_rows.push_back(this_row_num);
				k++;
			}
			else if(columns[k] > CSR.columns[j]) 
			{
				result.values.push_back(CSR.values[j]);
				result.columns.push_back(CSR.columns[j]);
				result_rows.push_back(CSR_row_num);
				j++;
			}
			else {
				T sum = values[k] + CSR.values[j];
				if (sum != 0) {
					result.values.push_back(sum);
					result.columns.push_back(columns[k]);
					result_rows.push_back(this_row_num);
				}
				//std::cout << std::endl << result << std::endl;
				j++;
				k++;
			}
		}
		else
		{
			if (this_row_num < CSR_row_num) 
			{
				result.values.push_back(values[k]);
				result.columns.push_back(columns[k]);
				result_rows.push_back(this_row_num);
				k++;
			}
			else
			{
				result.values.push_back(CSR.values[j]);
				result.columns.push_back(CSR.columns[j]);
				result_rows.push_back(CSR_row_num);
				j++;
			}
		}
	}
	while (k < values.getSize()) {
		result.values.push_back(values[k]);
		result.columns.push_back(columns[k]);
		result_rows.push_back(get_row(k));
		k++;
	}
	while (j < CSR.values.getSize())
	{
		result.values.push_back(CSR.values[j]); 
		result.columns.push_back(CSR.columns[j]);
		result_rows.push_back(CSR.get_row(j));
		j++;
	}
	size_t num_of_row = 0;
	size_t start = 0;
	size_t end = 0;
	for (size_t i = 0; i < size; i++)
	{
		bool is_find = false;
		for (size_t j = 0; j < result_rows.getSize(); j++)
		{
			if (result_rows[j] == i) {
				if (!is_find) {
					start = j;
					result.rows.push_back(j);
				}
				end = j;
				is_find = true;
			}
		}
		if (!is_find) {
			result.rows.push_back(end+1);
		}
	}
	result.rows.push_back(result.values.getSize());
	return result;
}

template<typename T>
inline TCompressedSparseRow<T> TCompressedSparseRow<T>::operator*(const TCompressedSparseRow<T>& CSR) const
{
	if (size != CSR.size) throw std::invalid_argument("sizes of matrix should be equal");
	const TCompressedSparseRow<T> CSR_transpose = CSR.transpose();
	TCompressedSparseRow<T> result(size);
	result.rows.clear();
	result.rows.push_back(0);
	size_t rows_size = rows.getSize();
	size_t CSR_transpose_rows_size = CSR_transpose.rows.getSize();
	for (size_t j = 1; j < rows_size; j++) {
		for (size_t i = 1; i < CSR_transpose_rows_size; i++)
		{
			{
				T sum = {};
				size_t t = CSR_transpose.rows[i - 1];
				size_t k = rows[j-1];
				for (; k < rows[j] && t < CSR_transpose.rows[i]; )
				{
					if (columns[k] < CSR_transpose.columns[t])
					{
						k++;
					}
					else if (columns[k] > CSR_transpose.columns[t])
					{
						t++;
					}
					else
					{
						sum += values[k] * CSR_transpose.values[t];
						k++;
						t++;
					}
				}
				if (sum != (T)0) {
					result.values.push_back(sum);
					result.columns.push_back(i - 1);
				}
			}
		}
		result.rows.push_back(result.values.getSize());
	}
	return result;
}

template<typename T>
inline TCompressedSparseRow<T> TCompressedSparseRow<T>::operator-(const TCompressedSparseRow& CSR) const
{
	return *this + (-CSR);
}

template<typename T>
inline TCompressedSparseRow<T> TCompressedSparseRow<T>::operator-() const noexcept
{
	TCompressedSparseRow<T> result(*this);
	for (size_t i = 0; i < result.values.getSize(); i++)
	{
		result.values[i] *= -1;
	}
	return result;
}
