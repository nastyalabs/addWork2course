#include "../inc/TCRSMatrix.h"

#include <vector>
#include <iostream>

int main()
{
    std::vector<std::vector<double>> matrix =
    {
        {1.0, 1.0, 5.0},
        {5.0, 2.0, 6.0},
        {1.0, 0.0, 3.0}
    };

    std::vector<std::vector<double>> matrix2 = 
    {
        {5.0, 3.0, -1.0},
        {1.0, 0.0, -1.0},
        {1.0, 1.0, -1.0}
    };

    TCRSMatrix<double> crsMatrix1(matrix);
    TCRSMatrix<double> crsMatrix2(matrix2);

    TCRSMatrix<double> result = crsMatrix1 * crsMatrix2;

    std::cout << crsMatrix2 << "\n";
    std::cout << "Transposed:\n" << ~crsMatrix2 << "\n";
    std::cout << "Multiplied:\n" << result << "\n";

    return 0;
}