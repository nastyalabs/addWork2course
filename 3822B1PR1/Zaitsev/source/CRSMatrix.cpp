#include "CRSMatrix.h"

CRSMatrix::CRSMatrix() : N(0), NZ(0) {}

CRSMatrix::CRSMatrix(size_t _N, int** matrix) : N(_N), NZ(0) { // не тот конструктор 
	int row = 0;
	row_ind.push_back(0);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			if (matrix[i][j] != 0) {
				values.push_back(matrix[i][j]);
				cols.push_back(j);
				row++;
			}
		}
		row_ind.push_back(row);
	}
	NZ = values.size();
}

CRSMatrix::CRSMatrix(size_t _N, size_t _NZ, vector<int> _values, vector<int> _cols, vector<int> _row_ind):
	N(_N),
	NZ(_NZ),
	values(_values),
	cols(_cols),
	row_ind(_row_ind)
{}

CRSMatrix::CRSMatrix(const CRSMatrix& other) : N(other.N), NZ(other.NZ) {
	values = vector<int>(other.values);
	cols = vector<int>(other.cols);
	row_ind = vector<int>(other.row_ind);
}

CRSMatrix::~CRSMatrix() {}

CRSMatrix& CRSMatrix::operator=(const CRSMatrix& other) {
	N = other.N;
	NZ = other.NZ;
	values = vector<int>(other.values);
	cols = vector<int>(other.cols);
	row_ind = vector<int>(other.row_ind);
	return *this;
}


CRSMatrix CRSMatrix::operator~() const {
	vector<int> nvalues(values);
	vector<int> ncols(cols);
	vector<int> nrow_ind;
	for (size_t i = 0; i < N + 1; i++) nrow_ind.push_back(0);
	for (size_t i = 0; i < NZ; i++) nrow_ind[cols[i] + 1]++;
	int s = 0;
	int tmp;
	for (size_t i = 1; i <= N; i++) {
		tmp = nrow_ind[i];
		nrow_ind[i] = s;
		s += tmp;
	}
	int j1, j2, col, ri, li;
	for (size_t i = 0; i < N; i++) {
		j1 = row_ind[i];
		j2 = row_ind[i+1];
		col = i;
		for (int j = j1; j < j2; j++) {
			ri = cols[j];
			li = nrow_ind[ri + 1];
			nvalues[li] = values[j];
			ncols[li] = col;
			nrow_ind[ri + 1]++;
		}
	}
	return CRSMatrix(N, NZ, nvalues, ncols, nrow_ind);
}

CRSMatrix CRSMatrix::operator*(const CRSMatrix& o) {
	CRSMatrix result, other = ~o;
	result.N = N;
	result.row_ind.push_back(0);

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			int amount = 0;
			int ks = row_ind[i];
			int ls = other.row_ind[j];
			int kf = row_ind[i + 1] - 1;
			int lf = other.row_ind[j + 1] - 1;
			while ((ks <= kf) && (ls <= lf)) {
				if (cols[ks] < other.cols[ls]) ks++;
				else if (cols[ks] > other.cols[ls]) ls++;
				else {
						amount += values[ks] * other.values[ls];
						ks++; ls++;
				}
			}
			if (amount != 0) {
				result.cols.push_back(j);
				result.values.push_back(amount);
				result.NZ++;
			}
		}
		result.row_ind.push_back(result.NZ);
	}
	return result;

}

ostream& operator<<(ostream& out, const CRSMatrix & v) {
	if (v.N <= 5) {
		int t_prev = 0;
		int t = 0;
		for (int i = 1; i < v.N + 1; i++) {
			int k = v.row_ind[i] - v.row_ind[i - 1];
			for (int j = 0; j < v.N; j++) {
				if ((v.cols[t] == j) && (k > t - t_prev)) {
					out << v.values[t] << " ";
					t++;
				}
				else out << "0 ";
			}
			t_prev = t;
			out << endl;
		}
	}
	else if (v.NZ <= 100) {
		out << "Values = { ";
		for (auto elem : v.values) out << elem << " ";
		out << "}" << endl << "Cols = { ";
		for (auto elem : v.cols) out << elem << " ";
		out << "}" << endl << "RowInds = { ";
		for (auto elem : v.row_ind) out << elem << " ";
		out << "}";
	}
	else out << "Matrix is too large to be printed";\

	return out;
}