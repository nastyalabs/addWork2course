#include "CRS.h"
#include "V1Matrix.h"
#include "VMatrix.h"
int main() {

    // �����-�� ������� ��������

    // ������ ������������� ��������� CRSMatrix
    int numRows = 3;
    int numCols = 3;
    std::vector<double> data = { 1.0, 0.0, 0.0, 0.0, 2.0, 0.0, 3.0, 4.0, 0.0 };

    CRSMatrix matrix(numRows, numCols, data);

    // ����� ��������� �������
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            std::cout << matrix.get(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;

    Matrix mat(3, 3); // ������� ������� 3x3

    // ��������� ������� ����������
    mat(0, 0) = 1.0;
    mat(1, 1) = 2.0;
    mat(2, 2) = 3.0;

    // ������� �������
    std::cout << "�������:" << std::endl;
    mat.print();

    // ������� ������
    std::vector<double> vec = { 1.0, 2.0, 3.0 };

    // �������� ������� �� ������
    std::vector<double> result = mat * vec;

    // ������� ��������� ���������
    std::cout << "��������� ��������� ������� �� ������:" << std::endl;
    for (double val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

}

