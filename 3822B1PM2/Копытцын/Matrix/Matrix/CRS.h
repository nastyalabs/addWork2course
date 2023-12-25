#pragma once
#include <iostream>
#include <vector>

struct CRSMatrix {
    std::vector<double> values;     // Значения элементов матрицы
    std::vector<int> column_indices; // Индексы столбцов для каждого элемента
    std::vector<int> row_pointers;   // Указатели на начало строк

    // Конструктор для создания матрицы
    CRSMatrix(int numRows, int numCols, const std::vector<double>& data) {
        // Проверка на корректное количество данных
        if (data.size() != numRows * numCols) {
            std::cerr << "Некорректное количество данных для матрицы" << std::endl;
            return;
        }

        row_pointers.push_back(0); // Начало первой строки

        for (int i = 0; i < numRows; ++i) {
            bool row_empty = true;

            for (int j = 0; j < numCols; ++j) {
                double val = data[i * numCols + j];
                if (val != 0.0) {
                    values.push_back(val);
                    column_indices.push_back(j);
                    row_empty = false;
                }
            }

            if (!row_empty) {
                row_pointers.push_back(row_pointers.back() + values.size() - row_pointers[row_pointers.size() - 1]);
            }
            else {
                row_pointers.push_back(row_pointers.back());
            }
        }
    }

    // Функция для получения элемента матрицы по индексам
    double get(int row, int col) const {
        int row_start = row_pointers[row];
        int row_end = row_pointers[row + 1];

        for (int i = row_start; i < row_end; ++i) {
            if (column_indices[i] == col) {
                return values[i];
            }
        }

        return 0.0; // Элемент отсутствует, возвращаем ноль
    }
};

