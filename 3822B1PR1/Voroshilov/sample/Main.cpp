#include "CRSMatrix.h"
#include "TestMultDuration.h"

int main()
{
	int n1, m1, n2, m2;
	n1 = m1 = n2 = m2 = 100;
	int  percent = 1;

	OneArrayMatrix oneArrMatr1(n1, m1);
	oneArrMatr1 = generateSparseMatrix(n1, m1, percent);
	OneArrayMatrix oneArrMatr2(n2, m2);
	oneArrMatr2 = generateSparseMatrix(n2, m2, percent);
	double oneArrayDuration = testOneArrayMult(oneArrMatr1, oneArrMatr2);
	cout << "OneArrayMult duration: " << oneArrayDuration << " sec." << endl;

	CoordinateMatrix coordMatr1(oneArrMatr1), coordMatr2(oneArrMatr2);
	double coordDuration = testCoordMult(coordMatr1, coordMatr2);
	cout << "CoordMult duration:    " << coordDuration << " sec." << endl;

	if (oneArrayDuration < coordDuration)
		cout << "OneArrayMult is " << coordDuration / oneArrayDuration << " times faster!";
	else
		cout << "CoordMult is " << oneArrayDuration / coordDuration << " times faster!";

	return 0;
}