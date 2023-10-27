#include "FlatMatrix.h"
#include "CRSMatrix.h"
#include <random>
#include <iostream>
#include <chrono>
using namespace std;

int** build(int n, bool is_sparse, int frequency = 10) {
	int** result = new int*[n];
	for (size_t i = 0; i < n; i++) result[i] = new int[n] {};
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			if (!is_sparse)
				result[i][j] = rand() % 9 + 1;
			else if (rand() % 100 < frequency + 1) result[i][j] = rand() % 10 + 1;
	return result;
}

double test_CRSMatrix(int tests, int size, int frequency) {
	double time = 0.0;
	for (size_t i = 0; i < tests; i++) {
		int** matrix1 = build(size, true, frequency);
		int** matrix2 = build(size, true, frequency);
		CRSMatrix A(size, matrix1), B(size, matrix2);
		auto start = chrono::steady_clock::now();
		A* B;
		auto end = chrono::steady_clock::now();
		auto diff = end - start; 
		time += chrono::duration<double, milli>(diff).count();
	}
	return time / tests;
}

int main(int argc, char* argv[]) {
	for (auto size : {500, 700, 1000, 2000, 3000, 4000}) {
		for (int frequency : {1}) {
			cout << "size: " << size << endl;
			cout << "Takes: " << test_CRSMatrix(1, size, frequency) << " ms";
			cout << endl << endl << endl;
		}
	}

	/*int sizes[] {100, 200, 300, 400};
	int frequencies[] {5, 10, 50, 100};


	for (bool is_sparse : {false, true}) {
		for (int size : sizes) {
			for (int frequency : frequencies) {
				int** matrix1 = build(size, is_sparse, frequency);
				int** matrix2 = build(size, is_sparse, frequency);
				FlatMatrix A(size, matrix1), B(size, matrix2);
				auto start = chrono::steady_clock::now();
				A* B;
				auto end = chrono::steady_clock::now();
				auto diff = end - start;
				cout << "FlatMatrices Multiplication for" << endl << "- size of " << size << endl << "- ";
				cout << (is_sparse ? "sparse" : "dense") << endl;
				if (is_sparse) cout << "- frequency is " << frequency << "%" << endl;
				cout << endl << "Takes " << chrono::duration<double, milli>(diff).count() << " ms";
				cout << endl << endl << endl;

				CRSMatrix A2(size, matrix1), B2(size, matrix2);
				start = chrono::steady_clock::now();
				A2 * B2;
				end = chrono::steady_clock::now();
				diff = end - start;
				cout << "CRSMatrix Multiplication for" << endl << "- size of " << size << endl << "- ";
				cout << (is_sparse ? "sparse" : "dense") << endl;
				if (is_sparse) cout << "- frequency is " << frequency << "%" << endl;
				cout << endl << "Takes " << chrono::duration<double, milli>(diff).count() << " ms";
				cout << endl << endl << endl;
				if (!is_sparse) break;
			}
		}
	}*/
}