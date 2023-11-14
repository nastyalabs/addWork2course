#include <iostream>
using namespace std;

#include "OneArrayMatrix.h"

class CRSMatrix
{
public:
    int n, m, nz;
    int* array, * cols, * rowIndex;
    OneArrayMatrix oneArrMatr;
    CRSMatrix(int _n, int _m);
    CRSMatrix(OneArrayMatrix& matr);
    CRSMatrix(CRSMatrix& matr);
    friend ostream& operator<<(ostream& ostr, const CRSMatrix& matr);
};