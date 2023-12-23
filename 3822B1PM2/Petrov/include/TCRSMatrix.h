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

    T* pMem;

    TDynamicMatrix<T> matrix;

public:
    TCRSMatrix(int _dim);
    TCRSMatrix(const TDynamicMatrix<T>& obj);
    TCRSMatrix(const TCRSMatrix<T>& obj);

    ~TCRSMatrix() { 
        delete[] cols; 
        delete[] rowIndex; 
        delete[] pMem; 
    }

    template <class U>
    friend std::ostream& operator<<(std::ostream& ostr, const TCRSMatrix<U>& obj);

};

template <class T>
TCRSMatrix<T>::TCRSMatrix(int _dim) {
    if (_dim < 1) {
        throw std::length_error("Invalid matrix size!");
    }

    this->dim = _dim;
    this->nz = 0;
    this->matrix = TDynamicMatrix<T>(dim);

    this->cols = nullptr;
    this->rowIndex = nullptr;
    this->pMem = nullptr;
}

template <class T>
TCRSMatrix<T>::TCRSMatrix(const TDynamicMatrix<T>& obj) {
    this->dim = obj.size();
    this->nz = 0;
    this->matrix = TDynamicMatrix<T>(obj);

    for (size_t i = 0; i < dim; i++) {
        for (size_t j = 0; j < dim; j++) {
            if (this->matrix[i][j]) { this->nz++; }
        }
    }

    this->pMem = new T[nz];
    this->cols = new int[nz];
    this->rowIndex = new int[dim + 1];

    for (size_t i = 0; i < nz; i++) {
        this->pMem[i] = 0;
        this->cols[i] = 0;
    }
    for (size_t i = 0; i < dim + 1; i++) {
        this->rowIndex[i] = 0;
    }

    int iElem = 0;
    int iRow = 0;

    for (size_t i = 0; i < dim; i++) {

        bool isRow = true;

        for (size_t j = 0; j < dim; j++) {
            if (this->matrix[i][j]) {

                this->pMem[iElem] = this->matrix[i][j];
                this->cols[iElem] = j;

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
    rowIndex[dim] = this->nz;
}

template <class T>
TCRSMatrix<T>::TCRSMatrix(const TCRSMatrix<T>& obj) {
    this->matrix = TDynamicMatrix(obj.matrix);
    this->dim = obj.dim;
    this->nz = obj.nz;

    this->pMem = new T[nz];
    this->cols = new int[nz];
    this->rowIndex = new int[dim + 1];

    for (size_t i = 0; i < this->nz; i++) {
        this->pMem[i] = obj.pMem[i];
        this->cols[i] = obj.cols[i];
    }
    for (size_t i = 0; i < this->dim + 1; i++) {
        this->rowIndex[i] = obj.rowIndex[i];
    }
}

template <class T>
std::ostream& operator<<(std::ostream& ostr, const TCRSMatrix<T>& obj)
{
    ostr << "pMem: ";
    for (size_t i = 0; i < obj.nz; i++) { ostr << obj.pMem[i] << " "; }
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
