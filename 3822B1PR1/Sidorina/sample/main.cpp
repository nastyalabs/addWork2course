#include "CRSMatrix.h"
#include "FlatMatrix.h"
#include <chrono>

int main() {
	double time = 0.0;
	cout << "Ordinary:" << endl;
	int n = 2;
	vector<int>v1 = { 1,2,3,4 };
	vector<int>v2 = { 1,2,3,4 };
	vector<int>v3(n * n);
	auto start = chrono::steady_clock::now();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			v3[i * n + j] = 0;
			for (int k = 0; k < n; k++) {
				v3[i * n + j] += v1[i * n + k] * v2[k * n + j];
			}
		}
	}
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	time += chrono::duration<double, milli>(diff).count();
	cout << time << endl;
	for (int i = 0; i < n * n; i++) {
		cout << v3[i]<<" ";
	}
	cout << endl;

	double time1 = 0.0;
	double time2 = 0.0;
	cout << "CRS:" << endl;

	int** m1 = new int* [3] {0};
	for (int i = 0; i < 3; i++) m1[i] = new int[3] {0};
	int** m2 = new int* [3] {0};
	for (int i = 0; i < 3; i++) m2[i] = new int[3] {0};
	m1[0][0] = 1;
	m1[0][2] = 3;
	m1[1][2] = 5;
	m1[2][2] = 7;

	m2[0][0] = 2;
	m2[0][1] = 5;
	m2[1][0] = 1;
	m2[2][2] = 8;
	CRSMatrix cm1(3, m1);
	CRSMatrix cm2(3, m2);
	auto start1 = chrono::steady_clock::now();
	cm1* cm2;
	auto end1 = chrono::steady_clock::now();
	auto diff1 = end1 - start1;
	time1 += chrono::duration<double, milli>(diff1).count();
	cout << time1 << endl;
	cout << cm1 * cm2 << endl;

	cout << "FlatMatrix:" << endl;
	FlatMatrix fm1(3, m1);
	FlatMatrix fm2(3, m2);
	auto start2 = chrono::steady_clock::now();
	fm1* fm2;
	auto end2 = chrono::steady_clock::now();
	auto diff2 = end2 - start2;
	time2 += chrono::duration<double, milli>(diff2).count();
	cout << time2 << endl;
	cout << fm1 * fm2 << endl;

}
