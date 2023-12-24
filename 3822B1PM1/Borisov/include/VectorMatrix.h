#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class VectorMatrix {
private:
    vector<vector<T>> els;
    size_t size;
public:
    VectorMatrix(size_t size) : size(size) {
        if (size < 1) {
            throw out_of_range("Matrix size should be greater than zero");
        }
        els = vector<vector<T>>(size, vector<T>(size, 0));
    }

    void setEl(size_t row, size_t col, T val) {
        if (row >= size || col >= size) {
            throw out_of_range("Invalid index");
        }
        els[row][col] = val;
    }

    T getEl(size_t row, size_t col) {
        if (row >= size || col >= size) {
            throw out_of_range("Invalid index");
        }
        return els[row][col];
    }

    VectorMatrix mult(VectorMatrix &other) {
        if (size != other.size) {
            throw out_of_range("Matrix sizes do not match for multiplication");
        }

        VectorMatrix<T> res(size);
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                for (size_t k = 0; k < size; k++) {
                    res.els[i][j] += els[i][k] * other.els[k][j];
                }
            }
        }
        return res;
    }

    VectorMatrix &operator=(VectorMatrix &other) {
        if (this != &other) {
            size = other.size;
            els = other.els;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const VectorMatrix<T> &matrix) {
        for (const auto &row: matrix.els) {
            for (const auto &elem: row) {
                out << elem << " ";
            }
            out << endl;
        }
        return out;
    }
};