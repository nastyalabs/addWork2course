#pragma once

#include <chrono>

#define NonZeroRate 0.5

#include <iostream>
#include <chrono>

#include "tmatrix.h"
#include "TCoordMatrix.h"
#include "TCRSMatrix.h"
#include "TFlatMatrix.h"
#include "tmatrix.h"

template <class T>
TDynamicMatrix<T> RandomDynamicMatrix(int dim = 5) {
	unsigned __int64 now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();  //geting time in ns
	//std::cout << now << std::endl;
	std::srand(now);

	if (dim < 1) {
		throw std::invalid_argument("Invalid matrix dimension!");
	}
	

	TDynamicMatrix<T> res(dim);
	int filledCells = (int)(dim * dim * NonZeroRate);

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
double FlatMatrixMultiply(TFlatMatrix<T>& m1, TFlatMatrix<T>& m2) {
	auto start = chrono::high_resolution_clock::now();					//start stamp with ns accuracy

	m1 * m2;

	auto stop = chrono::high_resolution_clock::now();					//stop stamp with ns accuracy

	chrono::duration<double> duration = stop - start;
	return duration.count();
}

template <class T>
double DynamicMatrixMultiply(TDynamicMatrix<T>& m1, TDynamicMatrix<T>& m2) {
	auto start = chrono::high_resolution_clock::now();					//start stamp with ns accuracy

	m1 * m2;

	auto stop = chrono::high_resolution_clock::now();					//stop stamp with ns accuracy

	chrono::duration<double> duration = stop - start;
	return duration.count();
}

template <class T>
double CoordMatrixMultiply(TCoordMatrix<T>& m1, TCoordMatrix<T>& m2) {

	auto start = chrono::high_resolution_clock::now();					//start stamp with ns accuracy

	m1 * m2;

	auto stop = chrono::high_resolution_clock::now();					//stop stamp with ns accuracy

	chrono::duration<double> duration = stop - start;
	return duration.count();
}