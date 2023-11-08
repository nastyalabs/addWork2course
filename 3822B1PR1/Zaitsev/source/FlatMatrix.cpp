#include "FlatMatrix.h"

FlatMatrix::FlatMatrix(int _N) : N(_N) {
	values = vector<int>(N * N);
}

FlatMatrix::FlatMatrix(int _N, int** matrix) : N(_N) {
	for (size_t i = 0; i < N; i++) 
		for (size_t j = 0; j < N; j++)
			values.push_back(matrix[i][j]);
}

FlatMatrix::FlatMatrix(const FlatMatrix& other) {
	N = other.N;
	values = vector<int>(other.values);
}

FlatMatrix::~FlatMatrix() {}

int FlatMatrix::get(size_t i, size_t j) const { return values[i * N + j]; }

void FlatMatrix::set(size_t i, size_t j, int value) { values[i * N + j] = value; }

FlatMatrix& FlatMatrix::operator=(const FlatMatrix& other) {
	N = other.N;
	values = vector<int>(other.values);
	return *this;
}

FlatMatrix FlatMatrix::operator*(const FlatMatrix& other) {
	FlatMatrix result(N);
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++) {
			int amount = 0;
			for (size_t k = 0; k < N; k++) 
				amount += get(i, k) * other.get(k, j);
			result.set(i, j, amount);
		}
	return result;
}

ostream& operator<<(ostream& out, const FlatMatrix& v) {
	for (size_t i = 0; i < v.N; i++) {
		for (size_t j = 0; j < v.N; j++)
			out << v.get(i, j) << "   ";
		out << endl;
	}
	return out;
}