#include <iostream>
using namespace std;

#include "OneArrayMatrix.h"

class CoordinateMatrix
{
    int n, m, nz;
    int* array, * rows, * cols;
    OneArrayMatrix oneArrMatr;
public:
    CoordinateMatrix(int _n, int _m);
    CoordinateMatrix(OneArrayMatrix& matr);
    friend ostream& operator<<(ostream& ostr, const CoordinateMatrix& matr);
    CoordinateMatrix CoordMult(CoordinateMatrix& matr);
};