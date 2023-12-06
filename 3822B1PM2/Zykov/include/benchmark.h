#include <iostream>
#include <chrono>

// without CRS multiplication

#include "tmatrix.h"
#include "TCOOMatrix.h"
#include "TCRSMatrix.h"
#include "TFlatMatrix.h"
#include "tmatrix.h"
#include "TVector.h"

template <class T>
TDynamicMatrix<T> createRndSparseMatrix(int rndSeed = 1000, int dim = 5, double fillingPercent = 0.5) {

	if (dim < 1) throw std::invalid_argument("Invalid matrix dimension!");
	if (fabs(fillingPercent) > 1.0) throw std::invalid_argument("Invalid percentage of filling!");
	srand(rndSeed);

	TDynamicMatrix<T> res(dim);
	int filledCells = (int)(dim * dim * fillingPercent);

	try { T tmp = (T)(rand() % 1000); }
	catch (const std::exception& e) { throw e; }

	while (filledCells > 0) {
		int x = rand() % dim;
		int y = rand() % dim;
		res[x][y] = (T)(rand() % 1000);

		filledCells--;
	}

	return res;
}

template <class T>
double testFlatMatrixMultiply(TFlatMatrix<T>& obj1, TFlatMatrix<T>& obj2) {

	auto start = chrono::high_resolution_clock::now();

	obj1 * obj2;

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;

	return duration.count();
}

template <class T>
double testDynamicMatrixMultiply(TDynamicMatrix<T>& obj1, TDynamicMatrix<T>& obj2) {

	auto start = chrono::high_resolution_clock::now();

	obj1 * obj2;

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;

	return duration.count();
}

template <class T>
double testCOOMatrixMultiply(TCOOMatrix<T>& obj1, TCOOMatrix<T>& obj2) {

	auto start = chrono::high_resolution_clock::now();

	obj1 * obj2;

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;

	return duration.count();
}