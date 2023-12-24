#pragma once

#include <iostream>
#include <vector>

#include "tflatmatrix.h"

template<typename T>
class TCRSMatrix
{
private:
    const size_t dimension;
    size_t nonZeroCount;
    std::vector<size_t> columns;
    std::vector<size_t> rowIndices;

    std::vector<T> data;
public:
    explicit
    TCRSMatrix(const std::vector<std::vector<T>>& matrix)
        : dimension(matrix.size())
    {
        size_t currentRow = 0;

        rowIndices.push_back(0);

        for (size_t y = 0; y < dimension; y++)
        {
            for (size_t x = 0; x < dimension; x++)
            {
                if (!matrix[y][x])
                    continue;

                data.push_back(matrix[y][x]);
                columns.push_back(x);
                currentRow++;
            }
            rowIndices.push_back(currentRow);
        }

        nonZeroCount = data.size();
    }

    TCRSMatrix(size_t dimension, std::vector<size_t> cols, std::vector<size_t> rowInd, std::vector<T> vals):
        dimension(dimension),
        nonZeroCount(vals.size()),
        columns(std::move(cols)),
        rowIndices(std::move(rowInd)),
        data(std::move(vals))
    {}

    TCRSMatrix operator~() const
    {
        TCRSMatrix result(dimension,
                std::vector<size_t>(columns),
                std::vector<size_t>(rowIndices.size()),
                std::vector<T>(data));

        for (size_t i = 0; i < dimension + 1; i++)
        {
            result.rowIndices.push_back(0);
        }
        for (size_t i = 0; i < nonZeroCount; i++)
        {
            result.rowIndices[columns[i] + 1]++;
        }

        size_t sum = 0;
        size_t temp;
        for (size_t i = 1; i <= dimension; i++)
        {
            temp = result.rowIndices[i];
            result.rowIndices[i] = sum;
            sum += temp;
        }

        size_t j1, j2, col, rowIdx, tempIdx;
        for (size_t i = 0; i < dimension; i++)
        {
            j1 = rowIndices[i];
            j2 = rowIndices[i + 1];
            col = i;
            for (size_t j = j1; j < j2; j++)
            {
                rowIdx = columns[j];
                tempIdx = result.rowIndices[rowIdx + 1];
                result.data[tempIdx] = data[j];
                result.columns[tempIdx] = col;
                result.rowIndices[rowIdx + 1]++;
            }
        }

        return result;
    }

    TCRSMatrix operator*(const TCRSMatrix& other) const
    {
        TCRSMatrix result(dimension, {}, {}, {});
        const TCRSMatrix transposed = ~other;

        result.rowIndices.push_back(0);

        size_t ks, ls, kf, lf;
        for (size_t i = 0; i < dimension; i++)
        {
            for (size_t j = 0; j < dimension; j++)
            {
                ks = rowIndices[i];
                ls = transposed.rowIndices[j];
                kf = rowIndices[i + 1] - 1;
                lf = transposed.rowIndices[j + 1] - 1;

                T accumulation{};
                while ((ks <= kf) && (ls <= lf)) {
                    if (columns[ks] < transposed.columns[ls]) {
                        ks++;
                    }
                    else if (columns[ks] > transposed.columns[ls]) {
                        ls++;
                    }
                    else {
                        accumulation += data[ks] * transposed.data[ls];
                        ks++;
                        ls++;
                    }
                }

                if (accumulation == 0) {
                    continue;
                }

                result.columns.push_back(j);
                result.data.push_back(accumulation);
                result.nonZeroCount++;
            }
            result.rowIndices.push_back(result.nonZeroCount);
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const TCRSMatrix& matrix)
    {
        for (const auto& element : matrix.data)
        {
            os << element << " ";
        }
        return os;
    }
};
