#ifndef CRS
#define CRS

#include <iostream>
#include <vector>

using std::ostream;
using std::vector;
using std::endl;

class CRSMatrix {

	size_t N;
	size_t NZ;
	vector<int> values;
	vector<int> cols;
	vector<int> row_ind;

public:
	
	CRSMatrix();
	CRSMatrix(size_t N, int** matrix);
	CRSMatrix(size_t N, size_t NZ, vector<int> values, vector<int>cols, vector<int> row_ind);
	CRSMatrix(const CRSMatrix& other);
	~CRSMatrix();

	CRSMatrix operator~() const; // transpose
	CRSMatrix& operator=(const CRSMatrix& other);
	CRSMatrix operator*(const CRSMatrix& other);
	friend ostream& operator<<(ostream& out, const CRSMatrix& v);
};


#endif