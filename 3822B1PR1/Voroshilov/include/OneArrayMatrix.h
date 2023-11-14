#include <iostream>
using namespace std;

class OneArrayMatrix
{
	int* array;
	int n, m;
public:
	OneArrayMatrix(int _n, int _m);
	OneArrayMatrix(OneArrayMatrix& matr);
	friend istream& operator>>(istream& istr, OneArrayMatrix& matr);
	friend ostream& operator<<(ostream& ostr, const OneArrayMatrix& matr);
	OneArrayMatrix OneArrayMult(OneArrayMatrix& matr);
};