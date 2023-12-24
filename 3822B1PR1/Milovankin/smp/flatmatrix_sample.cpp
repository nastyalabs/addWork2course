#include "../inc/TFlatMatrix.h"
#include <iostream>

int main()
{
    TFlatMatrix<int> flat1(4);
    flat1.at(0, 0) = 1;
    flat1.at(1, 2) = 2;
    flat1.at(2, 2) = 3;
    flat1.at(2, 3) = 4;
    std::cout << flat1 << '\n';

    TFlatMatrix<int> flat2(4);
    flat2.at(0, 0) = 1;
    flat2.at(1, 0) = 5;
    flat2.at(1, 1) = 6;
    flat2.at(2, 2) = 3;
    flat2.at(3, 3) = 4;
    std::cout << flat2 << '\n';

    std::cout << "matrix 1 + matrix 2\n"   << flat1 + flat2
              << "\nmatrix 1 - matrix 2\n" << flat1 - flat2
              << "\nmatrix 1 * matrix 2\n" << flat1 * flat2;
}