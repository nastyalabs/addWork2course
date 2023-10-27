#ifndef FLAT
#define FLAT

#include <iostream>
#include <vector>

using std::ostream;
using std::vector;
using std::endl;

class FlatMatrix {

	int N; // порядок матрицы
	vector<int> values;

public:

	FlatMatrix(int N);
	FlatMatrix(int N, int** matrix);
	FlatMatrix(const FlatMatrix& other);
	~FlatMatrix();

	int get(size_t i, size_t j) const;
	void set(size_t i, size_t j, int value);


	FlatMatrix& operator=(const FlatMatrix& other);
	FlatMatrix operator*(const FlatMatrix& other);
	friend ostream& operator<<(ostream& out, const FlatMatrix& v);

};

#endif