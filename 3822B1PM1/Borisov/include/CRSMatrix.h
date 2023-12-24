//
// Created by Sergey on 05.11.2023.
//

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class CRSMatrix {
private:
    size_t sz;
    vector<T> vals;
    vector<size_t> cols;
    vector<size_t> row_ind;
public:
    CRSMatrix(size_t size = 1) : sz(size) {
        if (sz < 0) {
            throw out_of_range("Matrix size should be greater than zero");
        }

        for (size_t i = 0; i <= sz; i++) {
            row_ind.push_back(0);
        }
    }

    void addEl(size_t row, size_t col, T val) {
        if (row < 0 || row >= sz || col < 0 || col >= sz) {
            throw out_of_range("Invalid index");
        }


        size_t sind = row_ind[row];


        size_t count_row = row_ind[row + 1] - row_ind[row];

        for (size_t i = row + 1; i <= sz; i++) {
            row_ind[i]++;
        }

        size_t now_ind = sind + count_row;
        for (size_t i = sind; i < sind + count_row; i++) {
            if (cols[i] > col) {
                now_ind = sind;
                continue;
            }
        }

        vals.insert(vals.begin() + now_ind, val);
        cols.insert(cols.begin() + now_ind, col);
    }


    void delEl(size_t row, size_t col) {
        if (row < 0 || row >= sz || col < 0 || col >= sz) {
            throw out_of_range("Invalid index");
        }


        size_t sind = row_ind[row];

        size_t count_row = row_ind[row + 1] - row_ind[row];

        for (size_t i = row + 1; i <= sz; i++) {
            row_ind[i]--;
        }

        size_t now_ind = -1;
        for (size_t i = sind; i < sind + count_row; i++) {
            if (cols[i] == col) {
                now_ind = sind;
                continue;
            }
        }

        if (now_ind == -1) {
            throw out_of_range("Invalid index");
        }

        vals.erase(vals.begin() + now_ind);
        cols.erase(cols.begin() + now_ind);
    }


    T getEl(size_t row, size_t col) {
        if (row < 0 || row >= sz || col < 0 || col >= sz) {
            throw out_of_range("Invalid index");
        }

        size_t sind = row_ind[row];
        size_t count_row = row_ind[row + 1] - row_ind[row];

        size_t now_ind = -1;
        for (size_t i = sind; i < sind + count_row; i++) {
            if (cols[i] == col) {
                return vals[i];
            }
        }

        return 0;
    }

    friend ostream &operator<<(ostream &os, CRSMatrix<T> &matrix) {
        for (size_t i = 0; i < matrix.sz; i++) {
            for (size_t j = matrix.row_ind[i]; j < matrix.row_ind[i + 1]; j++) {
                T val = matrix.vals[j];
                size_t col = matrix.cols[j];
                os << "(" << i << ";" << col << "): " << val << endl;
            }
        }
        return os;
    }

};
