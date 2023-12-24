#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class LinearMatrix {
private:
    vector<T> els;
    size_t size;

public:
    LinearMatrix(int size) : size(size) {
        if (size < 1) {
            throw out_of_range("Matrix size should be greater than zero");
        }
        els.resize(size * size);
    }

    void setEl(int row, int col, int value) {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            throw out_of_range("Invalid index");
        }
        els[row * size + col] = value;
    }


    T getEl(int row, int col) const{
        if (row < 0 || row >= size || col < 0 || col >= size) {
            throw out_of_range("Invalid index");
        }
        return els[row * size + col];
    }

    LinearMatrix mult(LinearMatrix &other) {
        if (size != other.size) {
            throw out_of_range("Matrix sizes do not match for multiplication");
        }

        LinearMatrix<T> res(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int sum = 0;
                for (int k = 0; k < size; ++k) {
                    sum += getEl(i, k) * other.getEl(k, j);
                }
                res.setEl(i, j, sum);
            }
        }
        return res;
    }

    LinearMatrix &operator=(LinearMatrix &other) {
        if (this != &other) {
            size = other.size;
            els = other.els;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const LinearMatrix& matrix) {
        for (int i = 0; i < matrix.size; i++) {
            for (int j = 0; j < matrix.size; j++) {
                os << matrix.getEl(i, j) << " ";
            }
            os << endl;
        }
        return os;
    }
};