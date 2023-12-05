#pragma once
#include <iostream>
#include "tmatrix.h"

template <class T>
class TCOOMatrix {
private:
    int dim;
    int nz;
    int* cols;
    int* rows;

    T* data;

    TDynamicMatrix<T> matrix;

public:
    TCOOMatrix(int _dim);
    TCOOMatrix(const TDynamicMatrix<T>& obj);
    TCOOMatrix(const TCOOMatrix<T>& obj) : matrix(obj.matrix), dim(obj.dim), nz(obj.nz) {

        this->data = new T[nz];
        this->cols = new int[nz];
        this->rows = new int[nz];

        for (size_t i = 0; i < nz; i++) {
            this->data[i] = obj.data[i];
            this->cols[i] = obj.cols[i];
            this->rows[i] = obj.rows[i];
        }
    }

    ~TCOOMatrix() { delete[] cols; delete[] rows; delete[] data; }

    template <class K> 
    friend std::ostream& operator<<(std::ostream& ostr, const TCOOMatrix<K>& obj);

    template <class K>
    friend TCOOMatrix<K> operator*(const TCOOMatrix<K>& obj1, const TCOOMatrix<K>& obj2);
};

template <class T>
TCOOMatrix<T>::TCOOMatrix(int _dim) {
    if (_dim < 1) throw std::length_error("Invalid matrix size!");
    dim = _dim;
    nz = 0;
    matrix = TDynamicMatrix<T>(dim);

    cols = nullptr;
    rows = nullptr;
    data = nullptr;
}

template <class T>
TCOOMatrix<T>::TCOOMatrix(const TDynamicMatrix<T>& obj) {

    matrix = TDynamicMatrix<T>(obj);
    dim = obj.size();
    nz = 0;

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (matrix[i][j]) { nz++; }
        }
    }

    data = new T[nz];
    rows = new int[nz];
    cols = new int[nz];

    size_t ind = 0;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (matrix[i][j]) {
                data[ind] = matrix[i][j];
                rows[ind] = i;
                cols[ind++] = j;
            }
        }
    }
}

template <class T>
std::ostream& operator<<(std::ostream& ostr, const TCOOMatrix<T>& obj)
{
    ostr << "data: ";
    for (size_t i = 0; i < obj.nz; i++) { ostr << obj.data[i] << " "; }
    ostr << std::endl;

    ostr << "rows: ";
    for (size_t i = 0; i < obj.nz; i++) { ostr << obj.rows[i] << " "; }
    ostr << std::endl;

    ostr << "cols: ";
    for (size_t i = 0; i < obj.nz; i++) { ostr << obj.cols[i] << " "; }
    ostr << std::endl;

    ostr << obj.matrix;

    return ostr;
}

template <class T>
TCOOMatrix<T> operator*(const TCOOMatrix<T>& obj1, const TCOOMatrix<T>& obj2) {
    if (obj1.dim != obj2.dim) throw std::length_error("Matrix sizes are not equal!");

    TDynamicMatrix<T> tmp(obj1.dim);

    for (size_t i = 0; i < obj1.nz; i++) {
        for (size_t j = 0; j < obj2.nz; j++) {
            if (obj1.cols[i] == obj2.rows[j]) {
                tmp[obj1.rows[i]][obj2.cols[j]] += obj1.data[i] * obj2.data[j];
            }
        }
    }

    TCOOMatrix<T> resMatrix(tmp);
    return resMatrix;
}
