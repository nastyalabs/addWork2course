#include <chrono>
#include "LinearMatrix.h"
#include "CRSMatrix.h"
#include "CoordMatrix.h"
#include "VectorMatrix.h"

using namespace chrono;

int main() {
    // заполненеи матрицы с 20% 0
    size_t size = 100;
    VectorMatrix<int> vm(size);


    // Установка 20% элементов в ноль
    srand(static_cast<unsigned int>(time(nullptr)));

    // Заполнение матрицы случайными числами
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            vm.setEl(i, j, rand() % 100 + 1);
        }
    }

    size_t zeroCount = size * size / 5; // 20%
    for (size_t i = 0; i < zeroCount; i++) {
        size_t row = rand() % size;
        size_t col = rand() % size;
        vm.setEl(row, col, 0);
    }

    // cout << vm;

    // ------------------ Вектор векторов ---------------------
    auto start = steady_clock::now();

    vm.mult(vm);

    auto end = steady_clock::now();
    auto elapsed = duration_cast<nanoseconds>(end - start);
    cout << "Vector matrix: " << elapsed.count() << " nanoseconds " << endl;

    // cout << vm.mult(vm);

    // ------------------ Линейная ---------------------
    LinearMatrix<int> lm(size);

    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            lm.setEl(i, j, vm.getEl(i, j));

    start = steady_clock::now();

    lm.mult(lm);

    end = steady_clock::now();
    elapsed = duration_cast<nanoseconds>(end - start);
    cout << "Linear matrix: " << elapsed.count() << " nanoseconds " << endl;

    // cout << lm.mult(lm);

    // ------------------ Покоординатная ---------------------

    CoordMatrix<int> cm(size);
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++) {
            int tmp = vm.getEl(i, j);
            if (tmp != 0)
                cm.setEl(i, j, tmp);
        }

    start = steady_clock::now();

    cm.mult(cm);

    end = steady_clock::now();
    elapsed = duration_cast<nanoseconds>(end - start);
    cout << "Coord matrix: " << elapsed.count() << " nanoseconds " << endl;

    // cout << cm.mult(cm);

}
