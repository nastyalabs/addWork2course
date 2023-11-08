#include "CRSMatrix.h"

CRSMatrix::CRSMatrix() {
	n = 0;
	nz = 0;
}
CRSMatrix::CRSMatrix(int n1, int** m) {
	n = n1;
	nz = 0;
	int row = 0;
	r_index.push_back(0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (m[i][j] != 0) {
				val.push_back(m[i][j]);
				col.push_back(j);
				row++;
			}
		}
		r_index.push_back(row);
	}
	nz = val.size();
}
CRSMatrix::CRSMatrix(int n1, int nz1, vector<int> val1, vector<int> col1, vector<int> r_index1) {
	n = n1;
	nz = nz1;
	val = val1;
	col = col1;
	r_index = r_index1;
}
CRSMatrix::CRSMatrix(const CRSMatrix& m) {
	n = m.n;
	nz = m.nz;
	val = vector<int>(m.val);
	col = vector<int>(m.col);
	r_index = vector<int>(m.r_index);
}
CRSMatrix::~CRSMatrix() {
}


CRSMatrix& CRSMatrix::operator=(const CRSMatrix& m) {
	n = m.n;
	nz = m.nz;
	val = vector<int>(m.val);
	col = vector<int>(m.col);
	r_index = vector<int>(m.r_index);
	return *this;
}
CRSMatrix CRSMatrix::operator~() const {
	vector<int>nval(val);
	vector<int>ncol(col);
	vector<int>nr_index;
	
	for (int i = 0; i < n + 1; i++) {
		nr_index.push_back(0);
	}
	for (int i = 0; i < nz; i++) {
		nr_index[col[i] + 1]++;
	}
	int s = 0;
	int tmp;
	for (int i = 1; i <= n; i++) {
		tmp = nr_index[i];
		nr_index[i] = s;
		s += tmp;
	}
	int j1, j2, c, ri, li;
	for (int i = 0; i < n; i++) {
		j1 = r_index[i];
		j2 = r_index[i+1];
		c = i;
		for (int j = j1; j < j2; j++) {
			ri = col[j];
			li = nr_index[ri + 1];
			nval[li] = val[j];
			ncol[li] = c;
			nr_index[ri + 1]++;

		}

	}
	return CRSMatrix(n, nz, nval, ncol, nr_index);
}
CRSMatrix CRSMatrix::operator*(const CRSMatrix& m) {
	CRSMatrix result;
	CRSMatrix other = ~m;
	result.n = n;
	result.r_index.push_back(0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int k = 0;
			int ks = r_index[i];
			int ls = other.r_index[j];
			int kf = r_index[i + 1] - 1;
			int lf = other.r_index[j + 1] - 1;
			while ((ks <= kf) && (ls <= lf)) {
				if (col[ks] < other.col[ls]) {
					ks++;
				}
				else {
					if (col[ks] > other.col[ls]) {
						ls++;
					}
					else {
						k += val[ks]*other.val[ls];
						ks++;
						ls++;
					}
				}
			}
			if (k > 0) {
				result.col.push_back(j);
				result.val.push_back(k);
				result.nz++;
			}


		}
		result.r_index.push_back(result.nz);


	}
	return result;
}

ostream& operator<<(ostream& ostr, const CRSMatrix& m) {
	ostr << "Values = { ";
	for (auto elem : m.val) ostr << elem << " ";
	ostr << "}" << endl << "Cols = { ";
	for (auto elem : m.col) ostr << elem << " ";
	ostr << "}" << endl << "RowInds = { ";
	for (auto elem : m.r_index) ostr << elem << " ";
	ostr << "}";
	return ostr;
}