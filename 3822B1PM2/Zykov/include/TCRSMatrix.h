#pragma once
#include <iostream>
#include "tmatrix.h"

template <class T>
class TCRSMatrix {
private:
    int dim;
    int nz;
    int* cols;
    int* rowIndex;

    T* data;

    TDynamicMatrix<T> matrix;

public:
    TCRSMatrix(int _dim);
    TCRSMatrix(const TDynamicMatrix<T>& obj);
    TCRSMatrix(const TCRSMatrix<T>& obj);

    ~TCRSMatrix() { delete[] cols; delete[] rowIndex; delete[] data; }

    template <class K>
    friend std::ostream& operator<<(std::ostream& ostr, const TCRSMatrix<K>& obj);

};

template <class T>
TCRSMatrix<T>::TCRSMatrix(int _dim) {
    if (_dim < 1) throw std::length_error("Invalid matrix size!");
    dim = _dim;
    nz = 0;
    matrix = TDynamicMatrix<T>(dim);

    cols = nullptr;
    rowIndex = nullptr;
    data = nullptr;
}

template <class T>
TCRSMatrix<T>::TCRSMatrix(const TDynamicMatrix<T>& obj) {
    dim = obj.size();
    nz = 0;
    matrix = TDynamicMatrix<T>(obj);

    for (size_t i = 0; i < dim; i++) {
        for (size_t j = 0; j < dim; j++) {
            if (matrix[i][j]) { nz++; }
        }
    }

    data = new T[nz];
    cols = new int[nz];
    rowIndex = new int[dim + 1];

    for (size_t i = 0; i < nz; i++) {
        data[i] = 0;
        cols[i] = 0;
    }
    for (size_t i = 0; i < dim + 1; i++) {
        rowIndex[i] = 0;
    }

    int iElem = 0;
    int iRow = 0;

    for (size_t i = 0; i < dim; i++) {

        bool isRow = true;

        for (size_t j = 0; j < dim; j++) {
            if (matrix[i][j]) {

                data[iElem] = matrix[i][j];
                cols[iElem] = j;

                if (isRow) {
                    rowIndex[iRow] = iElem;
                    isRow = false;
                    iRow++;
                }

                iElem++;

            }
        }
        if (isRow) {
            rowIndex[iRow] = iElem;
            iRow++;
        }
    }
    rowIndex[dim] = nz;
}

template <class T>
TCRSMatrix<T>::TCRSMatrix(const TCRSMatrix<T>& obj) {
    matrix = TDynamicMatrix(obj.matrix);
    dim = obj.dim;
    nz = obj.nz;

    data = new T[nz];
    cols = new int[nz];
    rowIndex = new int[dim + 1];

    for (size_t i = 0; i < this->nz; i++) {
        this->data[i] = obj.data[i];
        this->cols[i] = obj.cols[i];
    }
    for (size_t i = 0; i < this->dim + 1; i++) {
        this->rowIndex[i] = obj.rowIndex[i];
    }
}

template <class T>
std::ostream& operator<<(std::ostream& ostr, const TCRSMatrix<T>& obj)
{
    ostr << "data: ";
    for (size_t i = 0; i < obj.nz; i++) { ostr << obj.data[i] << " "; }
    ostr << std::endl;

    ostr << "rowIndex: ";
    for (size_t i = 0; i < obj.dim + 1; i++) { ostr << obj.rowIndex[i] << " "; }
    ostr << std::endl;

    ostr << "cols: ";
    for (size_t i = 0; i < obj.nz; i++) { ostr << obj.cols[i] << " "; }
    ostr << std::endl;

    ostr << obj.matrix;

    return ostr;
}
