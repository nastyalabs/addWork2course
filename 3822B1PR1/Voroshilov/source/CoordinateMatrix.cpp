#include "CoordinateMatrix.h"

CoordinateMatrix::CoordinateMatrix(int _n, int _m) : n(_n), m(_m), nz(0), oneArrMatr(_n, _m), array(0), rows(0), cols(0)
{

}

CoordinateMatrix::CoordinateMatrix(OneArrayMatrix& matr) : oneArrMatr(matr), n(matr.n), m(matr.m), nz(0)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (oneArrMatr.array[i * m + j])
                nz++;
    array = new int[nz];
    rows = new int[nz];
    cols = new int[nz];

    int ind = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (oneArrMatr.array[i * m + j])
            {
                array[ind] = oneArrMatr.array[i * m + j];
                rows[ind] = i;
                cols[ind++] = j;
            }
}

CoordinateMatrix::CoordinateMatrix(CoordinateMatrix& matr) : oneArrMatr(matr.oneArrMatr), n(matr.n), m(matr.m), nz(matr.nz), array(matr.array), rows(matr.rows), cols(matr.cols)
{

}

ostream& operator<<(ostream& ostr, const CoordinateMatrix& matr)
{
    ostr << "array: ";
    for (int i = 0; i < matr.nz; i++)
        ostr << matr.array[i] << " ";
    ostr << endl;

    ostr << "rows:  ";
    for (int i = 0; i < matr.nz; i++)
        ostr << matr.rows[i] << " ";
    ostr << endl;

    ostr << "cols:  ";
    for (int i = 0; i < matr.nz; i++)
        ostr << matr.cols[i] << " ";
    ostr << endl;

    ostr << matr.oneArrMatr;

    return ostr;
}

CoordinateMatrix CoordinateMatrix::CoordMult(CoordinateMatrix& matr)
{
    OneArrayMatrix oneArrRes(n, matr.m);
    for (int ind1 = 0; ind1 < nz; ind1++)
        for (int ind2 = 0; ind2 < matr.nz; ind2++)
            if (cols[ind1] == matr.rows[ind2])
                oneArrRes.array[rows[ind1] * oneArrRes.m + matr.cols[ind2]] += array[ind1] * matr.array[ind2];
    CoordinateMatrix coordRes(oneArrRes);
    return coordRes;
}