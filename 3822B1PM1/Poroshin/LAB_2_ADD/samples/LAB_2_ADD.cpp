// LAB_2_ADD.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <vector>
#include <chrono>
#include "Matrix1.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"
using namespace chrono;


int main()
{
	vector<int> A;
	int size = 0;
	while (1) {
		int tmp;
		cin >> tmp;
		A.push_back(tmp);
		size++;
		if (cin.peek() == '\n')
			break;
	}
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		arr[i] = A[i];
	}
	MATRIX<int> A_1(arr,size);
	MATRIX<int> B_1(arr,size);
	XY_MATRIX<int> A_2(arr, size);
	XY_MATRIX<int> B_2(arr, size);
	TDynamicMatrix<int> A_3((int)sqrt(size));
	TDynamicMatrix<int> B_3((int)sqrt(size));
	int k = 0;
	for (size_t i = 0; i < (int)sqrt(size); i++)
		for (size_t j = 0; j < (int)sqrt(size); j++) {
			A_3[i][j] = arr[k];
			B_3[i][j] = arr[k];
			k++;
		}


	cout << endl;
	cout << A_1 << endl;


	auto start = steady_clock::now();

	A_3* B_3;

	auto end = steady_clock::now();
	auto elapsed = duration_cast<nanoseconds>(end - start);
	cout << elapsed.count() << " nanoseconds " << endl;
	cout << endl;
	cout << A_3 * B_3 << endl;

	start = steady_clock::now();

	A_2 * B_2;

	end = steady_clock::now();
	elapsed = duration_cast<nanoseconds>(end - start);
	cout << elapsed.count() << " nanoseconds " << endl;
	cout << endl;
	cout << A_2 * B_2 << endl;

	start = steady_clock::now();

	A_1 * B_1;

	end = steady_clock::now();
	elapsed = duration_cast<nanoseconds>(end - start);
	cout << elapsed.count() << " nanoseconds " << endl;
	cout << endl;
	cout << A_1 * B_1 << endl;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
