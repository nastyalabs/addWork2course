#pragma once
#include <iostream>
#include <vector>

class Matrix {
public:
    // ����������� ��� �������� ������� � �������� ������ ����� � ��������
    Matrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
        data.resize(rows * cols, 0.0);
    }

    // ���������� ��������� () ��� ������� � ��������� �������
    double& operator()(int row, int col) {
        return data[row * cols + col];
    }

    // ���������� ��������� () ��� ������� � ��������� ������� (const ������)
    const double& operator()(int row, int col) const {
        return data[row * cols + col];
    }

    // ���������� ��������� ��������� ��� ��������� ������� �� ������
    std::vector<double> operator*(const std::vector<double>& vec) const {
        if (cols != static_cast<int>(vec.size())) {
            throw std::invalid_argument("������������ ������� ��� ��������� ������� � �������");
        }

        std::vector<double> result(rows, 0.0);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i] += data[i * cols + j] * vec[j];
            }
        }

        return result;
    }

    // ������� ��� ������ �������
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i * cols + j] << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    int rows;
    int cols;
    std::vector<double> data;
};