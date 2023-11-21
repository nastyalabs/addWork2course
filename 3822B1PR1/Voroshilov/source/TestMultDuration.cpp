#include "CoordinateMatrix.h"
#include <chrono>

OneArrayMatrix generateSparseMatrix(int n, int m, int percent)
{

	OneArrayMatrix matrRes(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if ((1 + std::rand() % 100) <= percent)
				matrRes.array[i * m + j] = std::rand();
	std::srand(time(NULL));
	return matrRes;
}

double testOneArrayMult(OneArrayMatrix& matr1, OneArrayMatrix& matr2)
{
	auto start = chrono::high_resolution_clock::now();
	matr1.OneArrayMult(matr2);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;

	return duration.count();
}

double testCoordMult(CoordinateMatrix& matr1, CoordinateMatrix& matr2)
{
	auto start = chrono::high_resolution_clock::now();
	matr1.CoordMult(matr2);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;

	return duration.count();
}