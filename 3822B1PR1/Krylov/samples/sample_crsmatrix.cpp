#include <iostream>
#include "tflatmatrix.h"
#include "tsparsematrix.h"

using namespace std;

int main()
{
    TFlatMatrix<int> flat(4);
    flat.at(0, 0) = 1;
    flat.at(1, 1) = 2;
    flat.at(2, 2) = 3;
    flat.at(3, 3) = 4;
    //
    std::cout << flat << std::endl;

    TCRSMatrix<int> sparse(flat);
    std::cout << sparse << std::endl << std::endl;

    std::cout << "-------*-------" << std::endl << std::endl;

    std::cout << flat * flat << std::endl << std::endl;
    std::cout << sparse * sparse << std::endl << std::endl;

    return 0;
}
