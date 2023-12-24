#include "matrix.h"
#include "XY.h"
#include "simple_matrix.h"
#include <chrono>

using namespace std;
typedef long long ll;

int main()
{
	size_t sz =600;
		cout << "size: " << sz << endl;
		double* mas = new double[sz];
		for (int i = 0; i < sz; ++i) mas[i] = rand() % 1000;

		matrix<double> a(mas, sz);
		matrix<double> b(mas, sz);
		xy<double> a1(mas, sz);
		xy<double> b1(mas, sz);
		TDynamicMatrix<double> a2(sz);
		TDynamicMatrix<double> b2(sz);
		for (int i = 0; i < sz; ++i)
		{
			for (int j = 0; j < sz; ++j)
			{
				a2[i][j] = rand() % 1000;
				b2[i][j] = rand() % 1000;
			}
		}

		auto start = chrono::steady_clock::now();
		a2* b2;
		auto finish = chrono::steady_clock::now();
		chrono::duration<double> elapsed_seconds{ finish - start };
		cout <<"matrix with vector: "<< elapsed_seconds.count() << endl;

		auto start1 = chrono::steady_clock::now();
		a1* b1;
		auto finish1 = chrono::steady_clock::now();
		chrono::duration<double> elapsed_seconds1{ finish1 - start1 };
		cout << "matrix with xy: " << elapsed_seconds1.count() << endl;

		auto start2 = chrono::steady_clock::now();
		a* b;
		auto finish2 = chrono::steady_clock::now();
		chrono::duration<double> elapsed_seconds2{ finish1 - start1 };
		cout << "matrix with line: " << elapsed_seconds2.count() << endl;
		cout << endl << endl << endl;
}