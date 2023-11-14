#include "CRSMatrix.h"

CRSMatrix::CRSMatrix(int _n, int _m) : n(_n), m(_m), nz(0), oneArrMatr(_n, _m), array(0), cols(0), rowIndex(0)
{

}

CRSMatrix::CRSMatrix(OneArrayMatrix& matr) : oneArrMatr(matr), n(matr.n), m(matr.m), nz(0)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (oneArrMatr.array[i * m + j])
                nz++;
    array = new int[nz];
    cols = new int[nz];
    rowIndex = new int[n + 1];

    int iElem = iRow = 0;
    for (int i = 0; i < n; i++)
    {
        bool rowFlag = true;
        for (int j = 0; j < m; j++)
            if (oneArrMatr.array[i * m + j])
            {
                array[iElem] = oneArrMatr.array[i * m + j];
                cols[iElem] = j;
                if (rowFlag)
                    rowIndex[iRow] = iElem;
                iElem++;
                iRow++;
            }
    }
}

CRSMatrix::CRSMatrix(CRSMatrix& matr) : oneArrMatr(matr.oneArrMatr), n(matr.n), m(matr.m), nz(matr.nz), array(matr.array), cols(matr.cols), rowIndex(matr.rowIndex)
{

}

ostream& operator<<(ostream& ostr, const CRSMatrix& matr)
{
    ostr << "array: ";
    for (int i = 0; i < matr.nz; i++)
        ostr << matr.array[i] << " ";
    ostr << endl;

    ostr << "cols:  ";
    for (int i = 0; i < matr.nz; i++)
        ostr << matr.cols[i] << " ";
    ostr << endl;

    ostr << "rowIndex: ";
    for (int i = 0; i < matr.n + 1; i++)
        ostr << matr.rowIndex[i] << " ";

    ostr << matr.oneArrMatr;

    return ostr;
}