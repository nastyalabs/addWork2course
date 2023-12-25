#pragma once
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector
{
protected:
	ValType* pVector;
	int Size;       // ������ �������
public:
	TVector(int s = 10);
	TVector(const TVector& v);                // ����������� �����������
	~TVector();
	int GetSize() { return Size; } // ������ �������
	ValType& operator[](int pos);             // ������
	bool operator==(const TVector& v) const;  // ���������
	bool operator!=(const TVector& v) const;  // ���������
	TVector& operator=(const TVector& v);     // ������������

	// ��������� ��������
	TVector  operator+(const ValType& val);   // ��������� ������
	TVector  operator-(const ValType& val);   // ������� ������
	TVector  operator*(const ValType& val);   // �������� �� ������

	// ��������� ��������
	TVector  operator+(const TVector& v);     // ��������
	TVector  operator-(const TVector& v);     // ���������
	ValType  operator*(const TVector& v);     // ��������� ������������

	// ����-�����
	friend istream& operator>>(istream& in, TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s)
{
	if (s > MAX_VECTOR_SIZE || s < 0)
		throw "Invalid size";
	Size = s;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = 0;
}

template <class ValType> //����������� �����������
TVector<ValType>::TVector(const TVector<ValType>& v)
{
	Size = v.Size;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++) {
		pVector[i] = v.pVector[i];
	}
}

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
}

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos < 0 || pos >= Size)
		throw "Index out of range";
	return pVector[pos];
}

template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (Size != v.Size)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != v.pVector[i])
			return false;
	return true;
}

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector& v) const
{
	return !(*this == v);
}

template <class ValType> // ������������
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
	if (this == &v)
		return *this;
	delete[] pVector;
	Size = v.Size;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];
	return *this;

}

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
	TVector<ValType> result(*this);
	for (int i = 0; i < Size; i++)
		result.pVector[i] += val;
	return result;
}

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
	TVector<ValType> result(*this);
	for (int i = 0; i < Size; i++)
		result.pVector[i] -= val;
	return result;
}

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
	TVector<ValType> result(*this);
	for (int i = 0; i < Size; i++)
		result.pVector[i] *= val;
	return result;
}

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw "The sizes should be the same";
	TVector<ValType> result(*this);
	for (int i = 0; i < Size; i++)
		result.pVector[i] = result.pVector[i] + v.pVector[i];
	return result;
}

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw "The sizes should be the same";
	TVector<ValType> result(*this);
	for (int i = 0; i < Size; i++)
		result.pVector[i] = result.pVector[i] - v.pVector[i];
	return result;
}

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw "The sizes should be the same";
	if (Size == 0 || v.Size == 0)
		throw "Invalid vector size";
	ValType result = 0;
	for (int i = 0; i < Size; i++)
		result += pVector[i] * v.pVector[i];
	return result;
}


// �������
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);                    // �����������
	TMatrix(const TVector<TVector<ValType> >& mt); // �������������� ����
	bool operator==(const TMatrix& mt) const;      // ���������
	bool operator!=(const TMatrix& mt) const;      // ���������
	TMatrix& operator= (const TMatrix& mt);        // ������������
	TMatrix  operator+ (const TMatrix& mt);        // ��������
	TMatrix  operator- (const TMatrix& mt);        // ���������

	// ���� / �����
	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE || s < 0)
		throw ("Invalid size");
	for (int i = 0; i < s; i++) {
		this->pVector[i] = TVector<ValType>(s);
	}
}

template <class ValType> // ����������� �����������
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ����������� �������������� ����
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ���������
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
	return TVector<TVector<ValType>>::operator==(mt);
}

template <class ValType> // ���������
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
	return !(*this == mt);
}

template <class ValType> // ������������
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
	if (this != &mt)
		TVector<TVector<ValType>>::operator=(mt);
	return *this;
}

template <class ValType> // ��������
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator+(mt);
}

template <class ValType> // ���������
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator-(mt);
}