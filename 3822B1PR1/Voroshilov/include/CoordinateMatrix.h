#pragma once
#include <iostream>
using namespace std;

#include "OneArrayMatrix.h"

class CoordinateMatrix
{
public:
    int n, m, nz;
    int* array, * rows, * cols;
    OneArrayMatrix oneArrMatr;
    CoordinateMatrix(int _n, int _m);
    CoordinateMatrix(OneArrayMatrix& matr);
    CoordinateMatrix(CoordinateMatrix& matr);
    friend ostream& operator<<(ostream& ostr, const CoordinateMatrix& matr);
    CoordinateMatrix CoordMult(CoordinateMatrix& matr);
};