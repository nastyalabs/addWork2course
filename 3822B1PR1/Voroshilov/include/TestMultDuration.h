#pragma once

#include "CoordinateMatrix.h"

OneArrayMatrix generateSparseMatrix(int n, int m, int percent);

double testOneArrayMult(OneArrayMatrix& matr1, OneArrayMatrix& matr2);

double testCoordMult(CoordinateMatrix& matr1, CoordinateMatrix& matr2);