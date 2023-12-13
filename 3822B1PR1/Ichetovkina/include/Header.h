#pragma once
#include <vector>
#include<iostream>
using namespace std;

class CRS {
	int N;
	int NZ;
	vector<int> val;
	vector<int> cols;
	vector<int> r_ind;

public:
	CRS();
	CRS(int _N, int freq);
	CRS(int _N, int _NZ, vector<int> _val, vector<int> _cols, vector<int> _r_ind);
	CRS(const CRS& m);
	~CRS(){};
	CRS& operator=(const CRS& m);
	CRS operator~() const;
	CRS operator*(const CRS& m);
	friend ostream& operator<<(ostream& out, const CRS& v);
};