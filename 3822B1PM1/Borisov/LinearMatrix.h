//
// Created by Sergey on 05.11.2023.
//

#include <iostream>

using namespace std;

template<typename T>
class LinearMatrix {
private:
    size_t sz;
    T *pMem;
public:
    LinearMatrix(size_t size = 1) : sz(size) {
        if (sz < 0) {
            throw out_of_range("Vector size should be greater than zero");
        }
        pMem = new T[sz * sz]();
        for (int i = 0; i < sz * sz; i++) {
            pMem[i] = 0;
        }
    }

    LinearMatrix &operator=(LinearMatrix &m1) {
        if (this == &m1) {
            return *this;
        }

        if (sz != m1.sz) {
            sz = m1.sz;
            delete[] pMem;
            pMem = new T[sz * sz]();

        }


        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                el(i, j) = m1.el(i, j);
            }
        }

        return *this;
    }


    ~LinearMatrix() {
        delete[] pMem;
    }

    T &el(size_t row, size_t col) {
        if ((row < 0) || (row >= sz) || (col < 0) || (col >= sz)) {
            throw out_of_range("Invalid index");
        }

        return pMem[sz * row + col];
    }

    LinearMatrix operator*(LinearMatrix &m1) {
        if (sz != m1.sz) {
            throw "Matrix sizes do not match for multiplication";
        }

        LinearMatrix res(sz);

        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                T sum = 0;
                for (size_t k = 0; k < sz; k++) {
                    sum += el(i, k) * m1.el(k, j);
                }
                res.el(i, j) = sum;
            }
        }

        return res;
    }


    friend ostream &operator<<(ostream &os, LinearMatrix &matrix) {
        for (size_t i = 0; i < matrix.sz; i++) {
            for (size_t j = 0; j < matrix.sz; j++) {
                os << matrix.el(i, j) << ' ';
            }
            os << endl;
        }
        return os;
    }
};
