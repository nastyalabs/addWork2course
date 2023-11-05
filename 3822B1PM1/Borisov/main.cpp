//
// Created by Sergey on 05.11.2023.
//
#include <chrono>
#include "LinearMatrix.h"
#include "CRSMatrix.h"
#include "CoordMatrix.h"

int main() {
    LinearMatrix<int> m1(2);
    m1.el(0, 0) = 1;
    m1.el(0, 1) = 2;
    m1.el(1, 0) = 3;
    m1.el(1, 1) = 4;

    LinearMatrix<int> m2(2);
    m2.el(0, 0) = 5;
    m2.el(0, 1) = 6;
    m2.el(1, 0) = 7;
    m2.el(1, 1) = 8;

    auto start = chrono::high_resolution_clock::now();
    LinearMatrix<int> m3 = m1 * m2;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << duration.count();
    return 0;
}
