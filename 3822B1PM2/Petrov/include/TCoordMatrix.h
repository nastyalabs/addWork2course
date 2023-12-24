#pragma once
#include <iostream>
#include "tmatrix.h"

template <class T>
class TCoordMatrix {
private:
    int dim;
    int nz;
    int* cols;
    int* rows;

    T* pMem;

    TDynamicMatrix<T> matrix;

public:
    TCoordMatrix(int _dim);
    TCoordMatrix(const TDynamicMatrix<T>& obj);
    TCoordMatrix(const TCoordMatrix<T>& obj) : matrix(obj.matrix), dim(obj.dim), nz(obj.nz) {

        this->pMem = new T[nz];
        this->cols = new int[nz];
        this->rows = new int[nz];

        for (size_t i = 0; i < nz; i++) {
            this->pMem[i] = obj.pMem[i];
            this->cols[i] = obj.cols[i];
            this->rows[i] = obj.rows[i];
        }
    }

    ~TCoordMatrix() { 
        delete[] cols; 
        delete[] rows; 
        delete[] pMem; 
    }

    TCoordMatrix<T> operator*(const TCoordMatrix<T>& obj);

    template <class U> 
    friend std::ostream& operator<<(std::ostream& ostr, const TCoordMatrix<U>& obj);
};

template <class T>
TCoordMatrix<T>::TCoordMatrix(int _dim) {
    if (_dim < 1) {
        throw std::length_error("Invalid matrix size!");
    }
    
    this->dim = _dim;
    this->nz = 0;
    this->matrix = TDynamicMatrix<T>(dim);

    this->cols = nullptr;
    this->rows = nullptr;
    this->pMem = nullptr;
}

template <class T>
TCoordMatrix<T>::TCoordMatrix(const TDynamicMatrix<T>& obj) {

    this->matrix = TDynamicMatrix<T>(obj);
    this->dim = obj.size();
    this->nz = 0;

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (matrix[i][j]) { nz++; }
        }
    }

    this->pMem = new T[nz];
    this->rows = new int[nz];
    this->cols = new int[nz];

    size_t ind = 0;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (matrix[i][j]) {
                this->pMem[ind] = matrix[i][j];
                rows[ind] = i;
                cols[ind++] = j;
            }
        }
    }
}

template <class T>
TCoordMatrix<T> TCoordMatrix<T>::operator*(const TCoordMatrix<T>& obj) {
    if (this->dim != obj.dim) throw std::length_error("Matrix sizes are not equal!");

    TDynamicMatrix<T> tmp(this->dim);

    for (size_t i = 0; i < this->nz; i++) {
        for (size_t j = 0; j < obj.nz; j++) {
            if (this->cols[i] == obj.rows[j]) {
                tmp[this->rows[i]][obj.cols[j]] += this->pMem[i] * obj.pMem[j];
            }
        }
    }

    TCoordMatrix<T> resMatrix(tmp);
    return resMatrix;
}

template <class T>
std::ostream& operator<<(std::ostream& ostr, const TCoordMatrix<T>& obj)
{
    ostr << "pMem: ";
    for (size_t i = 0; i < obj.nz; i++) { ostr << obj.pMem[i] << " "; }
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