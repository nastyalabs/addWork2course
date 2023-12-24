#pragma once
#include <chrono>
#include <random>
#include <iostream>
#include <iomanip>
#include "tcompressedsparserow.h"
#include "tmatrix.h"
#include "tcoordinatelist.h"
#include "telementsvector.h"
#define SETW_SIZE 15
#define MAX_SIZE 600
#define STEP 50
#define START_SIZE 100
//---------------------------------------------------------------------------
using namespace std;
template <typename T>
chrono::duration<double> test(T(*funk1)(const T&, const T&), const T& first, const T& second, T& result) {

    auto start = chrono::high_resolution_clock::now();
    result = funk1(first, second);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duraion = end - start;
    return duraion;
}

template <typename matrix, typename vector>
chrono::duration<double> test(vector(*funk1)(const matrix&, const vector&), const matrix& first, const vector& second, vector& result) {

    auto start = chrono::high_resolution_clock::now();
    result = funk1(first, second);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duraion = end - start;
    return duraion;
}
template <typename matrix, typename scalar>
chrono::duration<double> test(matrix(*funk1)(const matrix&, const scalar&), const matrix& first, const scalar& second, matrix& result) {

    auto start = chrono::high_resolution_clock::now();
    result = funk1(first, second);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duraion = end - start;
    return duraion;
}

template <typename T>
auto multiple = [](const T& m1, const T& m2) { return m1 * m2; };

template <typename matrix, typename vector>
auto multiple_with_vector = [](const matrix& m1, const vector& v) { return m1 * v; };

template <typename T>
auto multiple_with_scalar_dynamic_matrix = [](const TDynamicMatrix<T>& m1, const T& scalar) { return m1 * scalar; };
template <typename T>
auto multiple_with_scalar_CSR = [](const TCompressedSparseRow<T>& m1, const T& scalar) { return m1 * scalar; };
template <typename T>
auto multiple_with_scalar_TCL = [](const TCoordinateList<T>& m1, const T& scalar) { return m1 * scalar; };
template <typename T>
auto multiple_with_scalar_TEV = [](const TElementsVector<T>& m1, const T& scalar) { return m1 * scalar; };


template <typename T>
auto summary = [](const T& m1, const T& m2) { return m1 + m2; };

template <typename T>
auto substraction = [](const T& m1, const T& m2) { return m1 - m2; };

template <typename T>
TDynamicMatrix<T> dense_generator(size_t size) {
    TDynamicMatrix<T> randmatrix(size);
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            randmatrix[i][j] = rand() % 10 + 1;
        }
    }
    return randmatrix;
}
template <typename T>
TDynamicMatrix<T> sparse_generator(size_t size) {
    TDynamicMatrix<T> randmatrix(size);
    size_t amount = size / 4;
    for (size_t j = 0; j < amount; j++)
    {
        randmatrix[rand() % size][rand() % size] = rand() % 100;
    }
    //for (size_t i = 0; i < size; i++)
    //{
    //    for (size_t j = 0; j < size; j++)
    //    {
    //        randmatrix[i][j] = (rand() % 10 +1) * (i % 2) * (j % 2);
    //    }
    //}
    return randmatrix;
}
template <typename T>
TDynamicMatrix<T> half_filled_generator(size_t size) {
    TDynamicMatrix<T> randmatrix(size);
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            randmatrix[i][j] = (rand() % 10 + 1) * ((i * size + j) % 2);
        }
    }
    return randmatrix;
}
template <typename T>
TDynamicMatrix<T> generator(size_t size, size_t amount) {
    TDynamicMatrix<T> randmatrix(size);
    for (size_t j = 0; j < amount; j++)
    {
        randmatrix[rand() % size][rand() % size] = rand();
    }
    return randmatrix;
}


template<typename T>
void TestRunner(TDynamicMatrix<T>(*funk1)(const TDynamicMatrix<T>&, const TDynamicMatrix<T>&),
    TCompressedSparseRow<T>(*funk2)(const TCompressedSparseRow<T>&, const TCompressedSparseRow<T>&),
    TCoordinateList<T>(*funk3)(const TCoordinateList<T>&, const TCoordinateList<T>&),
    TElementsVector<T>(*funk4)(const TElementsVector<T>&, const TElementsVector<T>&),
    TDynamicMatrix<T>(*generator)(size_t)
)
{
    std::cout << std::setw(SETW_SIZE) << "size" << std::setw(SETW_SIZE) << "TDynamicMatrix" << std::setw(SETW_SIZE) << "CSR" << std::setw(SETW_SIZE) << "TCL" << std::setw(SETW_SIZE) << "TEV" << std::endl;
    for (size_t i = START_SIZE; i <= MAX_SIZE; i += STEP)
    {
        //generate
        TDynamicMatrix<T> m1 = generator(i);
        TDynamicMatrix<T> m2 = generator(i);

        //convert
        TCompressedSparseRow<T> CSR1(m1);
        TCompressedSparseRow<T> CSR2(m2);

        TCoordinateList<T> TCL1(m1);
        TCoordinateList<T> TCL2(m2);

        TElementsVector<T> TEV1(m1);
        TElementsVector<T> TEV2(m2);

        //result
        TDynamicMatrix<T> m3;
        TCompressedSparseRow<T> CSR3;
        TCoordinateList<T> TCL3;
        TElementsVector<T> TEV3;
        //cout << endl << endl << m1 << std::endl << m2 << endl;
        //tests
        std::cout << scientific << std::setw(SETW_SIZE) << i;
        std::cout << std::setw(SETW_SIZE) << test<TDynamicMatrix<T>>(funk1, m1, m2, m3).count();
        std::cout << std::setw(SETW_SIZE) << test<TCompressedSparseRow<T>>(funk2, CSR1, CSR2, CSR3).count();
        std::cout << std::setw(SETW_SIZE) << test<TCoordinateList<T>>(funk3, TCL1, TCL2, TCL3).count();
        std::cout << std::setw(SETW_SIZE) << test<TElementsVector<T>>(funk4, TEV1, TEV2, TEV3).count() << std::endl;

        //check
        TDynamicMatrix<T> CSR_result(CSR3);
        TDynamicMatrix<T> TCL_result(TCL3);
        TDynamicMatrix<T> TEV_result(TEV3);
        if (m3 != CSR_result) {
            cout << "wrong CSR";
            cout << std::endl << m1;
            cout << std::endl << m2;
            cout << std::endl << CSR_result;
            cout << std::endl << m3;
            break;
        }
        if (m3 != TCL_result) {
            cout << "wrong TCL";
            cout << std::endl << m1;
            cout << std::endl << m2;
            cout << std::endl << TCL_result;
            cout << std::endl << m3;
            break;
        }
        if (m3 != TEV_result) {
            cout << "wrong TEV";
            cout << std::endl << m1;
            cout << std::endl << m2;
            cout << std::endl << TEV_result;
            cout << std::endl << m3;
            break;
        }
    }
}

template<typename T>
void TestRunner(TDynamicMatrix<T>(*funk1)(const TDynamicMatrix<T>&, const T&),
    TCompressedSparseRow<T>(*funk2)(const TCompressedSparseRow<T>&, const T&),
    TCoordinateList<T>(*funk3)(const TCoordinateList<T>&, const T&),
    TElementsVector<T>(*funk4)(const TElementsVector<T>&, const T&),
    TDynamicMatrix<T>(*generator)(size_t)
)
{
    std::cout << std::setw(SETW_SIZE) << "size" << std::setw(SETW_SIZE) << "TDynamicMatrix" << std::setw(SETW_SIZE) << "CSR" << std::setw(SETW_SIZE) << "TCL" << std::setw(SETW_SIZE) << "TEV" << std::endl;
    for (size_t i = START_SIZE; i <= MAX_SIZE; i += STEP)
    {
        //generate
        TDynamicMatrix<T> m1 = generator(i);

        //convert
        TCompressedSparseRow<T> CSR1(m1);

        TCoordinateList<T> TCL1(m1);

        TElementsVector<T> TEV1(m1);


        //result
        TDynamicMatrix<T> m3;
        TCompressedSparseRow<T> CSR3;
        TCoordinateList<T> TCL3;
        TElementsVector<T> TEV3;

        //tests
        T sclalar = 8;
        std::cout << scientific << std::setw(SETW_SIZE) << i;
        std::cout << std::setw(SETW_SIZE) << test<TDynamicMatrix<T>, T>(funk1, m1, sclalar, m3).count();
        std::cout << std::setw(SETW_SIZE) << test<TCompressedSparseRow<T>, T>(funk2, CSR1, sclalar, CSR3).count();
        std::cout << std::setw(SETW_SIZE) << test<TCoordinateList<T>, T>(funk3, TCL1, sclalar, TCL3).count();
        std::cout << std::setw(SETW_SIZE) << test<TElementsVector<T>, T>(funk4, TEV1, sclalar, TEV3).count() << std::endl;

        //check
        TDynamicMatrix<T> CSR_result(CSR3);
        TDynamicMatrix<T> TCL_result(TCL3);
        TDynamicMatrix<T> TEV_result(TEV3);
        if (m3 != CSR_result) {
            cout << "wrong CSR";
            cout << std::endl << m1;
            //cout << std::endl << m2;
            cout << std::endl << CSR_result;
            cout << std::endl << m3;
            break;
        }
        if (m3 != TCL_result) {
            cout << "wrong TCL";
            cout << std::endl << m1;
            //cout << std::endl << m2;
            cout << std::endl << TCL_result;
            cout << std::endl << m3;
            break;
        }
        if (m3 != TEV_result) {
            cout << "wrong TEV";
            cout << std::endl << m1;
            //cout << std::endl << m2;
            cout << std::endl << TEV_result;
            cout << std::endl << m3;
            break;
        }
    }
}

template<typename T>
TDynamicVector<T> vector_generator(size_t size) {
    TDynamicVector<T> vector(size);
    for (size_t i = 0; i < size; i++)
    {
        vector[i] = rand() % 100;
    }
    return vector;
}
template<typename T>
void TestRunner(TDynamicVector<T>(*funk1)(const TDynamicMatrix<T>&, const TDynamicVector<T>&),
    TDynamicVector<T>(*funk2)(const TCompressedSparseRow<T>&, const TDynamicVector<T>&),
    TDynamicVector<T>(*funk3)(const TCoordinateList<T>&, const TDynamicVector<T>&),
    TDynamicVector<T>(*funk4)(const TElementsVector<T>&, const TDynamicVector<T>&),
    TDynamicMatrix<T>(*generator)(size_t),
    TDynamicVector<T>(*vec_generator)(size_t)
)
{
    std::cout << std::setw(SETW_SIZE) << "size" << std::setw(SETW_SIZE) << "TDynamicMatrix" << std::setw(SETW_SIZE) << "CSR" << std::setw(SETW_SIZE) << "TCL" << std::setw(SETW_SIZE) << "TEV" << std::endl;
    for (size_t i = START_SIZE; i <= MAX_SIZE; i += STEP)
    {
        //generate
        TDynamicMatrix<T> m1 = generator(i);
        TDynamicVector<T> v = vec_generator(i);

        //convert
        TCompressedSparseRow<T> CSR1(m1);

        TCoordinateList<T> TCL1(m1);

        TElementsVector<T> TEV1(m1);

        //result
        TDynamicVector<T> m3;
        TDynamicVector<T> CSR3;
        TDynamicVector<T> TCL3;
        TDynamicVector<T> TEV3;

        //tests
        std::cout << scientific << std::setw(SETW_SIZE) << i;
        std::cout << std::setw(SETW_SIZE) << test<TDynamicMatrix<T>, TDynamicVector<T>>(funk1, m1, v, m3).count();
        std::cout << std::setw(SETW_SIZE) << test<TCompressedSparseRow<T>, TDynamicVector<T>>(funk2, CSR1, v, CSR3).count();
        std::cout << std::setw(SETW_SIZE) << test<TCoordinateList<T>, TDynamicVector<T>>(funk3, TCL1, v, TCL3).count();
        std::cout << std::setw(SETW_SIZE) << test<TElementsVector<T>, TDynamicVector<T>>(funk4, TEV1, v, TEV3).count() << std::endl;

        //check
        if (m3 != CSR3) {
            cout << "wrong CSR";
            cout << std::endl << m1;
            cout << std::endl << v;
            cout << std::endl << CSR3;
            cout << std::endl << m3;
            break;
        }
        if (m3 != TCL3) {
            cout << "wrong TCL";
            cout << std::endl << m1;
            cout << std::endl << v;
            cout << std::endl << TCL3;
            cout << std::endl << m3;
            break;
        }
        if (m3 != TEV3) {
            cout << "wrong TEV";
            cout << std::endl << m1;
            cout << std::endl << v;
            cout << std::endl << TEV3;
            cout << std::endl << m3;
            break;
        }
    }
}

template<typename T>
void RunAllTests(string type) {
    cout << type <<" dense matrix sum" << endl;
    TestRunner<T>(summary<TDynamicMatrix<T>>,
        summary<TCompressedSparseRow<T>>,
        summary<TCoordinateList<T>>,
        summary<TElementsVector<T>>,
        dense_generator<T>
        );
    cout << type << " halth-filled matrix sum" << endl;
    TestRunner<T>(summary<TDynamicMatrix<T>>,
        summary<TCompressedSparseRow<T>>,
        summary<TCoordinateList<T>>,
        summary<TElementsVector<T>>,
        half_filled_generator<T>
        );
    cout << type << " sparse matrix sum" << endl;
    TestRunner<T>(summary<TDynamicMatrix<T>>,
        summary<TCompressedSparseRow<T>>,
        summary<TCoordinateList<T>>,
        summary<TElementsVector<T>>,
        sparse_generator<T>
        );
    cout << type << " dense matrix sub" << endl;
    TestRunner<T>(substraction<TDynamicMatrix<T>>,
        substraction<TCompressedSparseRow<T>>,
        substraction<TCoordinateList<T>>,
        substraction<TElementsVector<T>>,
        dense_generator<T>
        );
    cout << type << " halth-filled matrix sub" << endl;
    TestRunner<T>(substraction<TDynamicMatrix<T>>,
        substraction<TCompressedSparseRow<T>>,
        substraction<TCoordinateList<T>>,
        substraction<TElementsVector<T>>,
        half_filled_generator<T>
        );
    cout << type << " sparse matrix sub" << endl;
    TestRunner<T>(substraction<TDynamicMatrix<T>>,
        substraction<TCompressedSparseRow<T>>,
        substraction<TCoordinateList<T>>,
        substraction<TElementsVector<T>>,
        sparse_generator<T>
        );
    cout << type << " dense matrix multiplication" << endl;
    TestRunner<T>(multiple<TDynamicMatrix<T>>,
        multiple<TCompressedSparseRow<T>>,
        multiple<TCoordinateList<T>>,
        multiple<TElementsVector<T>>,
        dense_generator<T>
        );
    cout << type << " half-filled matrix multiplication" << endl;
    TestRunner<T>(multiple<TDynamicMatrix<T>>,
        multiple<TCompressedSparseRow<T>>,
        multiple<TCoordinateList<T>>,
        multiple<TElementsVector<T>>,
        sparse_generator<T>
        );
    cout << type << " sparse matrix multiplication" << endl;
    TestRunner<T>(multiple<TDynamicMatrix<T>>,
        multiple<TCompressedSparseRow<T>>,
        multiple<TCoordinateList<T>>,
        multiple<TElementsVector<T>>,
        sparse_generator<T>
        );
    cout << type << " dense matrix multiplication with vector" << endl;
    TestRunner<T>(multiple_with_vector<TDynamicMatrix<T>, TDynamicVector<T>>,
        multiple_with_vector<TCompressedSparseRow<T>, TDynamicVector<T>>,
        multiple_with_vector<TCoordinateList<T>, TDynamicVector<T>>,
        multiple_with_vector<TElementsVector<T>, TDynamicVector<T>>,
        dense_generator<T>,
        vector_generator<T>
        );
    cout << type << " half-filled matrix multiplication with vector" << endl;
    TestRunner<T>(multiple_with_vector<TDynamicMatrix<T>, TDynamicVector<T>>,
        multiple_with_vector<TCompressedSparseRow<T>, TDynamicVector<T>>,
        multiple_with_vector<TCoordinateList<T>, TDynamicVector<T>>,
        multiple_with_vector<TElementsVector<T>, TDynamicVector<T>>,
        half_filled_generator<T>,
        vector_generator<T>
        );
    cout << type << " sparse matrix multiplication with vector" << endl;
    TestRunner<T>(multiple_with_vector<TDynamicMatrix<T>, TDynamicVector<T>>,
        multiple_with_vector<TCompressedSparseRow<T>, TDynamicVector<T>>,
        multiple_with_vector<TCoordinateList<T>, TDynamicVector<T>>,
        multiple_with_vector<TElementsVector<T>, TDynamicVector<T>>,
        sparse_generator<T>,
        vector_generator<T>
        );
    cout << type << " dense matrix multiplication with scalar" << endl;
    TestRunner<T>(multiple_with_scalar_dynamic_matrix<T>,
        multiple_with_scalar_CSR<T>,
        multiple_with_scalar_TCL<T>,
        multiple_with_scalar_TEV<T>,
        dense_generator<T>
        );
    cout << type << " half-filled matrix multiplication with scalar" << endl;
    TestRunner<T>(multiple_with_scalar_dynamic_matrix<T>,
        multiple_with_scalar_CSR<T>,
        multiple_with_scalar_TCL<T>,
        multiple_with_scalar_TEV<T>,
        half_filled_generator<T>
        );
    cout << type << " sparse matrix multiplication with scalar" << endl;
    TestRunner<T>(multiple_with_scalar_dynamic_matrix<T>,
        multiple_with_scalar_CSR<T>,
        multiple_with_scalar_TCL<T>,
        multiple_with_scalar_TEV<T>,
        sparse_generator<T>
        );
}