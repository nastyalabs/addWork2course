#include "OneArrayMatrix.h"
#include "CoordinateMatrix.h"
#include <chrono>

int main()
{
	int n1, m1, n2, m2;

	/*cout << "n1: ";
	cin >> n1;
	cout << "m1: ";
	cin >> m1;
	cout << endl;
	OneArrayMatrix oneArrMatr1(n1, m1);
	cout << "Matrix1 " << n1 << "*" << m1 << ":" << endl;
	cin >> oneArrMatr1;
	cout << endl;

	n2 = m1;
	cout << "n2= " << n2 << endl << "m2: ";
	cin >> m2;
	cout << endl;
	OneArrayMatrix oneArrMatr2(n2, m2);
	cout << "Matrix2 " << n2 << "*" << m2 << ":" << endl;
	cin >> oneArrMatr2;
	cout << endl;*/


	n1 = 1000;
	m1 = n2 = 500;
	m2 = 1000;

	OneArrayMatrix oneArrMatr1(n1, m1);
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m1; j++)
			if (i == j)
				oneArrMatr1.array[i * m1 + j] = i + j;

	OneArrayMatrix oneArrMatr2(n2, m2);
	for (int i = 0; i < n2; i++)
		for (int j = 0; j < m2; j++)
			if (i == j)
				oneArrMatr2.array[i * m2 + j] = i - j;


	OneArrayMatrix oneArrRes(n1, m2);

	auto start1 = chrono::high_resolution_clock::now();
	oneArrRes = oneArrMatr1.OneArrayMult(oneArrMatr2);
	auto end1 = chrono::high_resolution_clock::now();
	chrono::duration<double> oneArrDuration = end1 - start1;

	//cout << "OneArrayMult:" << endl << oneArrRes;
	cout << "OneArrayMult duration: " << oneArrDuration.count() << " sec" << endl << endl;


	CoordinateMatrix coordMatr1(oneArrMatr1), coordMatr2(oneArrMatr2);
	CoordinateMatrix coordRes(n1, m2);

	auto start2 = chrono::high_resolution_clock::now();
	coordRes = coordMatr1.CoordMult(coordMatr2);
	auto end2 = chrono::high_resolution_clock::now();
	chrono::duration<double> coordDuration = end2 - start2;

	//cout << "CoordMult:" << endl << coordRes;
	cout << "CoordMult duration: " << coordDuration.count() << " sec" << endl << endl;

	if (oneArrDuration.count() > coordDuration.count())
		cout << "CoordMult is " << oneArrDuration.count() / coordDuration.count() << " times faster than oneArrayMult" << endl;
	else
		cout << "OneArrayMult is " << coordDuration.count() / oneArrDuration.count() << " times faster than oneArrayMult" << endl;

	return 0;
}