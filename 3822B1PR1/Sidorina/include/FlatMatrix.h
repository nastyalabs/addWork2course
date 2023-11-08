
#pragma once
#include <iostream>
#include <vector>

using namespace std;

class FlatMatrix {
	int n;
	vector<int> val;
public:
	FlatMatrix(int n);
	FlatMatrix(int n, int** m);
	FlatMatrix(const FlatMatrix& m);
	~FlatMatrix();
	int get(int i, int j) const;
	void set(int i, int j, int val);
	FlatMatrix operator*(const FlatMatrix& m);
	FlatMatrix& operator=(const FlatMatrix& m);
	friend ostream& operator<<(ostream& ostr, const FlatMatrix& m);
};
