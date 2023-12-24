#pragma once
#include "tvector.h"
#include "tmatrix.h"
#include <limits>



template <typename T>
struct TContainer {
public:
	T value;
	size_t row;
	size_t column;
	TContainer() {
		value = 0;
		row = 0;
		column = 0;
	}
	TContainer(const T& _value, size_t _row, size_t _column) : value(_value), row(_row), column(_column) {}
	TContainer(const TContainer& container) {
		value = container.value;
		row = container.row;
		column = container.column;
	}
	friend std::ostream& operator<< (std::ostream& stream, const TContainer<T>& container) {
		stream << container.value << std::setw(10) << container.row << std::setw(10) << container.column;
		return stream;
	}
	bool operator< (const TContainer<T>& container) const {
		if (row < container.row) return true;
		if (row > container.row) return false;
		if (column < container.column) return true;
		return false;
	}
	bool operator> (const TContainer<T>& container) const {
		if (row > container.row) return true;
		if (row < container.row) return false;
		if (column > container.column) return true;
		return false;
	}
	bool operator== (const TContainer<T>& container) const {
		if ((row == container.row) && (column == container.row)) return true;
		return false;
	}
};


template <typename T>
class TCoordinateList {
	Vector<TContainer<T>> data;
	size_t size;
	size_t binary_search(size_t start, size_t end, size_t row, size_t column, bool& is_contains) const;
public:
	TCoordinateList(size_t _size = 1) : data(), size(_size) {}
	TCoordinateList(const TCoordinateList& tcoordlist) : data(tcoordlist.data), size(tcoordlist.size) {}
	operator TDynamicMatrix<T>() {
		TDynamicMatrix<T> result(size);
		size_t sz = data.getSize();
		for (size_t i = 0; i < sz; i++)
		{
			result[data[i].row][data[i].column] = data[i].value;
		}
		return result;
	}
	void QuickSort(Vector<TContainer<T>>& arr, int left, int right) const {
		//unsigned long int compare = 0, swaps = 0;
		int i = left;
		int j = right;
		TContainer<T> mid = arr[(i + j) / 2];
		while (i <= j) {
			while (arr[i] < mid) {
				i++;
				//(*compare)++;
			}
			while (arr[j] > mid) {
				j--;
				//(* compare)++;
			}
			if (i <= j) {
				std::swap(arr[i], arr[j]);
				/*(*swaps)++;*/
				i++;
				j--;
			}
			//(*compare)++;
		}
		if (j > left) {
			QuickSort(arr, left, j);
		}
		if (i < right) {
			QuickSort(arr, i, right);
		}
		//(*compare) += 2;
	}
	TCoordinateList<T> transpose() const {
		TCoordinateList result(size);
		Vector<TContainer<T>> res = this->data;
		size_t sz = res.getSize();
		for (size_t i = 0; i < sz; i++)
		{
			std::swap(res[i].column, res[i].row);
		}
		QuickSort(res, 0, sz - 1);
		result.data = res;
		return result;
	}

	TCoordinateList(const TDynamicMatrix<T>& matrix)
	{
		size = matrix.size();
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if (matrix[i][j] != 0) {
					data.push_back(TContainer<T>(matrix[i][j], i, j));
				}
			}
		}
	}
	Vector<size_t> GetRows() const {
		Vector<size_t> rows;// = Vector<size_t>(size + 1);
		//size_t row = 0;
		//rows[0] = 0;
		//size_t sz = data.getSize();
		//for (size_t i = 0; i < sz; i++)
		//{
		//	if (data[i].row > row) {
		//		row++;
		//		rows[row] = i;
		//	}
		//}
		//rows[size] = sz;
		//return rows;
		size_t start = 0;
		size_t end = 0;
		for (size_t i = 0; i < size; i++)
		{
			bool is_find = false;
			for (size_t j = 0; j < data.getSize(); j++)
			{
				if (data[j].row == i) {
					if (!is_find)
					{
						start = j;
						rows.push_back(j);
					}
					end = j;
					is_find = true;
				}
			}
			if (!is_find) {
				rows.push_back(end + 1);
			}
		}
		rows.push_back(data.getSize());
		return rows;
	}
	const T& get(size_t row, size_t column) const
	{
		if ((row > size) || (column > size)) throw std::out_of_range("TCoordinateList try to get out of range value");
		if (data.getSize() == 0) return 0;
		bool is_exist = false;
		size_t pos = binary_search(0, data.getSize() - 1, row, column, is_exist);
		if (!is_exist) return (T)0;
		return data[pos].value;
	}
	void set(const T& elem, size_t row, size_t column)
	{
		if ((row > size) || (column > size)) throw std::out_of_range("TCoordinateList try to set out of range value");
		TContainer<T> record(elem, row, column);
		if (data.getSize() == 0) {
			data.push_back(record);
			return;
		}
		bool is_exist = false;
		size_t pos = binary_search(0, data.getSize() - 1, row, column, is_exist);
		if (is_exist)
			data[pos] = record;
		else
			data.insert(pos, record);
	}

	bool operator==(const TCoordinateList& m) const noexcept;
	bool operator!=(const TCoordinateList& m) const noexcept
	{
		return !(*this == m);
	}

	TCoordinateList operator*(const T& val) const;


	TDynamicVector<T> operator*(const TDynamicVector<T>& v) const;
	//TCoordinateList<T> operator+(const TDynamicVector<T>& v) const;

	TCoordinateList operator+(const TCoordinateList& m) const;
	TCoordinateList<T> operator-(const TCoordinateList& m) const;
	TCoordinateList operator-() const;
	TCoordinateList operator*(const TCoordinateList& m) const;


	//friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
	//{
	//	for (size_t i = 0; i < v.sz; i++)
	//	{
	//		istr >> v.pMem[i];
	//	}
	//	return istr;
	//}
	friend std::ostream& operator<<(std::ostream& ostr, const TCoordinateList<T>& v)
	{
		size_t sz = v.data.getSize();
		for (size_t i = 0; i < sz; i++)
		{
			ostr << v.data[i] << std::endl;
		}
		return ostr;
	}
};
template <typename T>
size_t TCoordinateList<T>::binary_search(size_t start, size_t end, size_t row, size_t column, bool& is_contains) const
{
	if (end - start < 5) {
		size_t i = start;
		for (; i <= end; i++)
		{
			if ((data[i].row == row))
			{
				if (data[i].column == column)
				{
					is_contains = true;
					return i;
				}
				if (data[i].column > column) {
					is_contains = false;
					return i;
				}
			}
			else if (data[i].row > row)
			{
				is_contains = false;
				return i;
			}
		}
		is_contains = false;
		return i;
	}
	size_t middle = start / 2 + end / 2;
	if (data[middle].row == row) {
		if (data[middle].column == column)
		{
			is_contains = true;
			return middle;
		}
		if (data[middle].column > column)
			return binary_search(start, middle - 1, row, column, is_contains);
		else
			return binary_search(middle + 1, end, row, column, is_contains);
	}
	else if (data[middle].row < row)
		return binary_search(middle + 1, end, row, column, is_contains);
	else
		return binary_search(start, middle - 1, row, column, is_contains);
}

template<typename T>
bool TCoordinateList<T>::operator==(const TCoordinateList<T>& m) const noexcept
{
	if (size != m.size) return false;
	size_t sz = m.data.getSize();
	for (size_t i = 0; i < sz; i++)
	{
		if (m.data[i].value != data[i].value)
			return false;
	}
	return true;
}

template<typename T>
inline TCoordinateList<T> TCoordinateList<T>::operator*(const T& val) const
{
	TCoordinateList<T> result(*this);
	size_t sz = data.getSize();
	for (size_t i = 0; i < sz; i++)
	{
		result.data[i].value = data[i].value * val;
	}
	return result;
}

template<typename T>
inline TDynamicVector<T> TCoordinateList<T>::operator*(const TDynamicVector<T>& v) const
{
	if (size != v.size()) throw std::invalid_argument("sizes of TCoordinateList and TDynamicVector are not equal");
	TDynamicVector<T> result(size);
	Vector<size_t> row = GetRows();
	for (size_t i = 1; i < row.getSize(); i++)
	{
		T sum = {};
		for (size_t j = row[i - 1]; j < row[i]; j++)
		{
			sum += data[j].value * v[data[j].column];
		}
		result[i - 1] = sum;
	}
	return result;
}

template<typename T>
inline TCoordinateList<T> TCoordinateList<T>::operator+(const TCoordinateList<T>& m) const
{
	if (size != m.size) throw std::invalid_argument("matrices are not equal");
	size_t m_sz = m.data.getSize();
	size_t sz = data.getSize();
	size_t i = 0;
	size_t j = 0;
	TCoordinateList<T> result(size);
	while (i < sz && j < m_sz) 
	{
		if (data[i].row == m.data[j].row)
		{
			if (data[i].column == m.data[j].column)
			{
				T sum = data[i].value + m.data[j].value;
				if (sum != (T)0) {
					result.data.push_back(TContainer<T>(sum, data[i].row, data[i].column));
				}
				++i;
				++j;
			}
			else if (data[i].column < m.data[j].column)
			{
				result.data.push_back(data[i]);
				++i;
			}
			else
			{
				result.data.push_back(m.data[j]);
				++j;
			}
		}
		else if (data[i].row < m.data[j].row)
		{
			result.data.push_back(data[i]);
			++i;
		}
		else
		{
			result.data.push_back(m.data[j]);
			++j;
		}
	}
	while (i < sz)
	{
		result.data.push_back(data[i]);
		i++;
	}
	while (j < m_sz) 
	{
		result.data.push_back(m.data[j]);
		j++;
	}
	return result;
}

template<typename T>
inline TCoordinateList<T> TCoordinateList<T>::operator-(const TCoordinateList<T>& m) const
{
	return *this + (-m);
}

template<typename T>
inline TCoordinateList<T> TCoordinateList<T>::operator-() const
{
	TCoordinateList<T> result(size);
	size_t sz = data.getSize();
	result.data.resize(sz);
	for (size_t i = 0; i < sz; i++)
	{
		result.data[i].value = -data[i].value;
		result.data[i].column = data[i].column;
		result.data[i].row = data[i].row;
	}
	return result;
}

template<typename T>
inline TCoordinateList<T> TCoordinateList<T>::operator*(const TCoordinateList<T>& m) const
{
	if (size != m.size) throw std::invalid_argument("matrices are not equal");
	TCoordinateList<T> m_transpose = m.transpose();
	Vector<size_t> this_rows = this->GetRows();
	Vector<size_t> m_rows = m_transpose.GetRows();
	size_t rows_size = this_rows.getSize();
	TCoordinateList<T> result(size);
	for (size_t j = 1; j < rows_size; j++) {
		for (size_t i = 1; i < m_rows.getSize(); i++)
		{
			{
				T sum = {};
				size_t t = m_rows[i - 1];
				size_t k = this_rows[j - 1];
				for (; k < this_rows[j] && t < m_rows[i]; )
				{
					if (data[k].column < m_transpose.data[t].column)
					{
						k++;
					}
					else if (data[k].column > m_transpose.data[t].column)
					{
						t++;
					}
					else
					{
						sum += data[k].value * m_transpose.data[t].value;
						k++;
						t++;
					}
				}
				if (sum != (T)0) {
					result.data.push_back(TContainer<T>(sum, j - 1, i - 1));
				}
			}
		}
	}
	return result;
}
