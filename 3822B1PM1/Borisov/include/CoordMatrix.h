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
        if (sz < 1) {
            throw out_of_range("Matrix size should be greater than zero");
        }

        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                els.push_back({i, j, T(0)});
            }
        }
    }

    void setEl(size_t row, size_t col, T val) {
        if (row >= sz || col >= sz) {
            throw out_of_range("Invalid index");
        }

        for (auto& elem : els) {
            if (elem.row == row && elem.col == col) {
                elem.val = val;
                return;
            }
        }

        els.push_back(MElement<T>{row, col, val});
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
        if (row >= sz || col >= sz) {
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

    CoordMatrix mult(CoordMatrix &m) {
        if (sz != m.sz) {
            throw out_of_range("Matrix sizes do not match for multiplication");
        }

        CoordMatrix<T> res(sz);

        for (const auto& el1 : els) {
            for (const auto& el2 : m.els) {
                if (el1.col == el2.row) {
                    T tmp = el1.val * el2.val;
                    size_t res_row = el1.row;
                    size_t res_col = el2.col;

                    bool found = false;
                    for (auto& res_elem : res.els) {
                        if (res_elem.row == res_row && res_elem.col == res_col) {
                            res_elem.val += tmp;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        res.els.push_back({res_row, res_col, tmp});
                    }
                }
            }
        }

        return res;
    }

    friend ostream& operator<<(ostream& os, const CoordMatrix& matrix) {
        for (size_t i = 0; i < matrix.sz; i++) {
            for (size_t j = 0; j < matrix.sz; j++) {
                bool found = false;
                for (const auto& elem : matrix.els) {
                    if (elem.row == i && elem.col == j) {
                        os << elem.val << " ";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    os << T(0) << " ";
                }
            }
            os << "\n";
        }
        return os;
    }


};
