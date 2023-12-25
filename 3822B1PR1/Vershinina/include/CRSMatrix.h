#pragma once
#include <iostream>
#include <vector>

using namespace std;




class CRSMatrix {
	int n;
	int nz;
	vector<int> val;
	vector<int> col;
	vector<int> r_index;
public:
	CRSMatrix();
	CRSMatrix(int n, int** m);
	CRSMatrix(int n, int nz, vector<int> val, vector<int> col, vector<int> r_index);
	CRSMatrix(const CRSMatrix& m);
	~CRSMatrix();
	CRSMatrix operator*(const CRSMatrix& m);
	CRSMatrix& operator=(const CRSMatrix& m);
	CRSMatrix operator~() const;
	friend ostream& operator<<(ostream& ostr, const CRSMatrix& m);
};