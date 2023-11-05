//
// Created by Sergey on 05.11.2023.
//

#include <iostream>
#include <vector>

using namespace std;


template<typename T>
struct MElement {
    size_t row;
    size_t col;
    T val;
};


template<typename T>
class CoordMatrix {
private:
    vector<MElement<T>> els;
    size_t sz;
public:
    CoordMatrix(size_t size = 1) : sz(size) {
        if (sz < 0) {
            throw out_of_range("Matrix size should be greater than zero");
        }
    }

    // TODO: проверка на существование
    void addEl(size_t row, size_t col, T val) {
        if (row < 0 || row >= sz || col < 0 || col >= sz) {
            throw out_of_range("Invalid index");
        }

        MElement<T> m = {row, col, val};
        els.push_back(m);
    }

    void delEl(size_t row, size_t col) {
        if (row < 0 || row >= sz || col < 0 || col >= sz) {
            throw out_of_range("Invalid index");
        }

        int f = 0;
        for (size_t i = 0; i < els.size(); i++) {
            MElement<T> elem = els[i];
            if (elem.col == col && elem.row == row) {
                els.erase(els.begin() + i);
                f = 1;
            }
        }
        if (!f) {
            throw out_of_range("Invalid index");
        }
    }

    T getEl(size_t row, size_t col) {
        if (row < 0 || row >= sz || col < 0 || col >= sz) {
            throw out_of_range("Invalid index");
        }

        for (size_t i = 0; i < els.size(); i++) {
            MElement<T> elem = els[i];
            if (elem.col == col && elem.row == row) {
                return elem.val;
            }
        }
        return 0;
    }

    CoordMatrix operator*(CoordMatrix &m1) {
        if (sz != m1.sz) {
            throw "Matrix sizes do not match for multiplication";
        }

        CoordMatrix res(sz);

        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                T sum = 0;
                for (size_t k = 0; k < sz; k++) {

                    sum += (*this).getEl(i, k) * m1.getEl(k, j);
                }
                res.addEl(i, j, sum);
            }
        }

        return res;
    }

    friend ostream &operator<<(ostream &os, CoordMatrix &matrix) {
        for (size_t i = 0; i < matrix.els.size(); i++) {
            MElement<T> elem = matrix.els[i];
            os << "(" << elem.row << ";" << elem.col << "): " << elem.val << endl;
        }
        return os;
    }
};
