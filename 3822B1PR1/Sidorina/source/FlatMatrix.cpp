#include "FlatMatrix.h"
FlatMatrix::FlatMatrix(int n1) {
	n = n1;
	val = vector<int>(n * n);
}
FlatMatrix::FlatMatrix(int n1, int** m) {
	n = n1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			val.push_back(m[i][j]);
		}
	}
}
FlatMatrix::FlatMatrix(const FlatMatrix& m) {
	n = m.n;
	val = vector<int>(m.val);
}
FlatMatrix::~FlatMatrix() {
}
int FlatMatrix::get(int i, int j) const {
	return val[i*n + j];
}
void FlatMatrix::set(int i, int j, int v) {
	val[i*n + j]=v;
}
FlatMatrix& FlatMatrix::operator=(const FlatMatrix& m) {
	n = m.n;
	val = vector<int>(m.val);
	return *this;
}
FlatMatrix FlatMatrix::operator*(const FlatMatrix& m) {
	FlatMatrix result(n);
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int k = 0;
			for (int l = 0; l < n; l++) {
				k += get(i, l) * m.get(l, j);
			}
			result.set(i, j, k);
		}
	}
	return result;
}

ostream& operator<<(ostream& ostr, const FlatMatrix& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			ostr << m.get(i, j) << " ";
		}
		ostr << endl;
	}
	return ostr;
}