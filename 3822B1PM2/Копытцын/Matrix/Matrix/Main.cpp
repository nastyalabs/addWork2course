#include "CRS.h"
#include "V1Matrix.h"
#include "VMatrix.h"
int main() {

    // Какая-то базовая проверка

    // Пример использования структуры CRSMatrix
    int numRows = 3;
    int numCols = 3;
    std::vector<double> data = { 1.0, 0.0, 0.0, 0.0, 2.0, 0.0, 3.0, 4.0, 0.0 };

    CRSMatrix matrix(numRows, numCols, data);

    // Вывод элементов матрицы
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            std::cout << matrix.get(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;

    Matrix mat(3, 3); // Создаем матрицу 3x3

    // Заполняем матрицу значениями
    mat(0, 0) = 1.0;
    mat(1, 1) = 2.0;
    mat(2, 2) = 3.0;

    // Выводим матрицу
    std::cout << "Матрица:" << std::endl;
    mat.print();

    // Создаем вектор
    std::vector<double> vec = { 1.0, 2.0, 3.0 };

    // Умножаем матрицу на вектор
    std::vector<double> result = mat * vec;

    // Выводим результат умножения
    std::cout << "Результат умножения матрицы на вектор:" << std::endl;
    for (double val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

}

