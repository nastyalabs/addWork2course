#include"Header.h"
CRS::CRS() {
	N = 0;
	NZ = 0;
}
CRS::CRS(int _N, int freq) {
	N = _N;
	NZ = 0;
	int r = 0;
	r_ind.push_back(0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (rand() % 100 < freq + 1) {
				int x = rand() % 10 + 1;
				val.push_back(x);
				cols.push_back(j);
				r++;
			}
		}
		r_ind.push_back(r);
	}
	NZ = val.size();
}
CRS::CRS(int _N, int _NZ, vector<int> _val, vector<int> _cols, vector<int> _r_ind) {
	N = _N;
	NZ = _NZ;
	val = _val;
	cols = _cols;
	r_ind = _r_ind;
}
CRS::CRS(const CRS& m) {
	N = m.N;
	NZ = m.NZ;
	val = vector<int>(m.val);
	cols = vector<int>(m.cols);
	r_ind = vector<int>(m.r_ind);
}
CRS& CRS::operator=(const CRS& m) {
	N = m.N;
	NZ = m.NZ;
	val = vector<int>(m.val);
	cols = vector<int>(m.cols);
	r_ind = vector<int>(m.r_ind);
	return *this;
}
CRS CRS::operator~() const {
	vector<int> nval = val;
	vector<int> ncols = cols;
	vector<int> n_r_ind;
	int sum = 0;
	for (int i = 0; i <= N; i++) {
		n_r_ind.push_back(0);
	}
	for (int i = 0; i < NZ; i++) {
		n_r_ind[cols[i] + 1]++;
	}
	int t;
	for (int i = 1; i <= N; i++) {
		t = n_r_ind[i];
		n_r_ind[i] = sum;
		sum += t;
	}
	int m, n, c, r, l;
	for (int i = 0; i < N; i++) {
		m = r_ind[i];
		n = r_ind[i + 1];
		c = i;
		for (int j = m; j < n; j++) {
			r = cols[j];
			l = n_r_ind[r + 1];
			nval[l] = val[j];
			ncols[l] = c;
			n_r_ind[r + 1] += 1;

		}
	}
	return CRS(N, NZ, nval, ncols, n_r_ind);
}
CRS CRS::operator*(const CRS& m) {
	CRS res;
	CRS inv = ~m;
	res.N = N;
	res.r_ind.push_back(0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int num = 0;
			int ks = r_ind[i];
			int ls = inv.r_ind[j];
			int kf = r_ind[i + 1] - 1;
			int lf = inv.r_ind[j + 1] - 1;
			while ((ks <= kf) && (ls <= lf)) {
				if (cols[ks] > inv.cols[ls])ls++;
				else {
					if (cols[ks] > inv.cols[ls]) ls++;
					else {
						num += val[ks] * inv.val[ls];
						ks++;
						ls++;
					}
				}
			}
			if (num > 0) {
				res.cols.push_back(j);
				res.val.push_back(num);
				res.NZ++;
			}
		}
		res.r_ind.push_back(NZ);
	}
	return res;
}
ostream& operator<<(ostream& out, const CRS& m) {
	out << "Values = {";
	for (auto el : m.val) {
		out << el << " ";
	}
	out << "}" << endl << "Cols = { ";
	for (auto el : m.cols) {
		out << el << " ";
	}
	out << "}" << endl << "RowInds = { ";
	for (auto el : m.r_ind) {
		out << el << " ";
	}
	out << "}";
	return out;
}