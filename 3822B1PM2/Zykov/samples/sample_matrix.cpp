#include "benchmark.h"
#include <iostream>
#include <chrono>

#define ITERATIONS 100
#define PERCENTAGE 0.5
#define RND_SEED 100242

void main() {

	for (size_t i = 2; i < ITERATIONS; i++) {

		double dT, cT, fT;

		TDynamicMatrix<int> dynamicMatrixA = createRndSparseMatrix<int>(RND_SEED + 1000, i, PERCENTAGE);
		TDynamicMatrix<int> dynamicMatrixB = createRndSparseMatrix<int>(RND_SEED - 1000, i, PERCENTAGE);

		dT = testDynamicMatrixMultiply<int>(dynamicMatrixA, dynamicMatrixB);

		TCOOMatrix<int> cooMatrixA(dynamicMatrixA);
		TCOOMatrix<int> cooMatrixB(dynamicMatrixB);

		cT = testCOOMatrixMultiply<int>(cooMatrixA, cooMatrixB);

		TFlatMatrix<int> flatMatrixA(i);
		TFlatMatrix<int> flatMatrixB(i);

		for (size_t k = 0; k < i; k++) {
			for (size_t j = 0; j < i; j++) {
				flatMatrixA(k, j) = dynamicMatrixA[k][j];
				flatMatrixB(k, j) = dynamicMatrixB[k][j];
			}
		}

		fT = testFlatMatrixMultiply<int>(flatMatrixA, flatMatrixB);

		std::cout << "Dim: " << i << std::endl << "DYNAMIC | COO | FLAT" << std::endl << dT << " " << cT << " " << fT << std::endl << std::endl;

	}
}
