#ifndef __TSPARSEMATRIX_H__
#define __TSPARSEMATRIX_H__

#include <iostream>
#include <vector>

#include "tflatmatrix.h"

template<typename T>
class TCRSMatrix
{
private:
    const size_t N;
    size_t NZ;
    std::vector<size_t> cols;
    std::vector<size_t> idx_row;

    std::vector<T> values;
public:
    explicit
    TCRSMatrix(const TFlatMatrix<T>& matrix)
        : N(matrix.size())
    {
        size_t row = 0;

        //
        idx_row.push_back(0);
        //

        for (size_t y = 0; y < N; y++)
        {
            for (size_t x = 0; x < N; x++)
            {
                if (!matrix.at(y, x))
                    continue;

                values.push_back(matrix.at(y, x));
                cols.push_back(x);
                row++;
            }
            idx_row.push_back(row);
        }

        NZ = values.size();
    }

    TCRSMatrix(size_t N, std::vector<size_t> cols, std::vector<size_t> row_ind, std::vector<T> values)
        : N(N)
        , NZ(values.size())
        , cols(std::move(cols))
        , idx_row(std::move(row_ind))
        , values(std::move(values))
    {}

    TCRSMatrix operator~() const
    {
        TCRSMatrix result(N,
                std::vector<size_t>(cols),
                std::vector<size_t>(idx_row.size()),
                std::vector<T>(values));

        for (size_t i = 0; i < N + 1; i++)
        {
            result.idx_row.push_back(0);
        }
        for (size_t i = 0; i < NZ; i++)
        {
            result.idx_row[cols[i] + 1]++;
        }

        size_t s = 0;
        size_t buf;
        for (size_t i = 1; i <= N; i++)
        {
            buf = result.idx_row[i];
            result.idx_row[i] = s;
            s += buf;
        }

        size_t j1, j2, col, ri, li;
        for (size_t i = 0; i < N; i++)
        {
            j1 = idx_row[i];
            j2 = idx_row[i + 1];
            col = i;
            for (size_t j = j1; j < j2; j++)
            {
                ri = cols[j];
                li = result.idx_row[ri + 1];
                result.values[li] = values[j];
                result.cols[li] = col;
                result.idx_row[ri + 1]++;
            }
        }

        return result;
    }

    TCRSMatrix operator*(const TCRSMatrix& other) const
    {
        TCRSMatrix result(N, {}, {}, {});
        const TCRSMatrix transposed = ~other;

        result.idx_row.push_back(0);

        size_t ks, ls, kf, lf;
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                ks = idx_row[i];
                ls = transposed.idx_row[j];
                kf = idx_row[i + 1] - 1;
                lf = transposed.idx_row[j + 1] - 1;

                T acc{};
                while ((ks <= kf) && (ls <= lf)) {
                    if (cols[ks] < transposed.cols[ls]) {
                        ks++;
                    }
                    else if (cols[ks] > transposed.cols[ls]) {
                        ls++;
                    }
                    else {
                        acc += values[ks] * transposed.values[ls];
                        ks++;
                        ls++;
                    }
                }

                if (acc == 0) {
                    continue;
                }

                result.cols.push_back(j);
                result.values.push_back(acc);
                result.NZ++;
            }
            result.idx_row.push_back(result.NZ);
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const TCRSMatrix& m)
    {
        ostr << "Elements: [ ";
        for (const auto& e : m.values) {
            ostr << e << " ";
        }
        ostr << "]" << std::endl;

        ostr << "Cols { ";
        for (const auto& idx : m.cols) {
            ostr << idx << " ";
        }
        ostr << "}" << std::endl;

        ostr << "Rows { ";
        for (const auto& idx : m.idx_row) {
            ostr << idx << " ";
        }
        ostr << "}";

        return ostr;
    }
};

#endif // __TSPARSEMATRIX_H__
