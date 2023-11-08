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

void show_correctness() {
	cout << "=============    MULT CORRECTNESS PRESENTATION    =============" << endl;

	int** m1 = new int* [3]{ 0 };
	for (int i = 0; i < 3; i++) m1[i] = new int[3]{ 0 };
	m1[0][0] = 1; // Premake for matrix A:
	m1[0][2] = 3; // 1 0 3
	m1[1][2] = 5; // 0 0 5
	m1[2][2] = 7; // 0 0 7

	int** m2 = new int* [3]{ 0 };
	for (int i = 0; i < 3; i++) m2[i] = new int[3]{ 0 };
	m2[0][0] = 2; // Premake for matrix B:
	m2[0][1] = 5; // 2 5 0
	m2[1][0] = 1; // 1 0 0
	m2[2][2] = 8; // 0 0 8

	int** m3 = new int* [3]{ 0 };
	for (int i = 0; i < 3; i++) m3[i] = new int[3]{ 0 };
	m3[0][0] = 2;
	m3[0][1] = 5;  // Premake for expected result of A*B
	m3[0][2] = 24; // 2 5 24
	m3[1][2] = 40; // 0 0 40
	m3[2][2] = 56; // 0 0 56

	CRSMatrix A(3, m1), B(3, m2), exp_AB(3, m3);
	cout << "Matrix A:" << endl << A << endl;
	cout << "Matrix B:" << endl << B << endl;
	cout << "Matrix A * B:" << endl << A * B << endl;
	cout << "Expected result of A * B:" << endl << exp_AB << endl;
}

void Flat_CRS_comparison() {
	cout << "=============    FlatMatrix and CRSMatrix Multiplication comparison    =============" << endl << endl;
	for (bool is_sparse : {false, true}) {
		for (int size : {100, 200, 300, 400}) {
			for (int frequency : {5, 10, 50, 100}) {
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
	}
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


void test_average_time_CRS(int times, vector<int> sizes, vector<int> frequencies) {
	cout << "=============    CRSMatrix Multiplicaition average time    =============" << endl;
	cout << "by the results of " << times << " executions:  " << endl << endl;
	for (int size : sizes) 
		for (int frequency : frequencies) 
			cout << "Size = " << size << ", Frequency = " << frequency << "%" << endl << "Time: " << test_CRSMatrix(times, size, frequency) << " ms" << endl << endl;
}



int main(int argc, char* argv[]) {
	show_correctness();
	//Flat_CRS_comparison();
	//test_average_time_CRS(10, {10, 100, 1000}, {1, 5, 10, 20, 50});
	//test_average_time_CRS(2, {500, 700, 1000, 2000, 3000, 4000}, {1});

	
}