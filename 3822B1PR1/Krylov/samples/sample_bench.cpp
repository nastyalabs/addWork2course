#include <iostream>
#include "tbenchmark.h"
#include "tflatmatrix.h"
#include "tsparsematrix.h"

//#define _GENERATE_MARKDOWN

void run_benchmarks(size_t N, int probability, int number_order)
{
    int rand_val;

    TFlatMatrix<int> flat(N);
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            rand_val = rand() % number_order;
            flat.at(i, j) = ((rand_val % 100) <= probability) ? rand_val : 0;
        }
    }
    TCRSMatrix<int> sparse(flat);

    TSimpleBenchmark<std::chrono::milliseconds> benchmark;

    benchmark.reset();
    auto mlt_flat = flat * flat;
    auto elapsed_flat = benchmark.elapsed();

    benchmark.reset();
    auto mlt_sparse = sparse * sparse;
    auto elapsed_sparse = benchmark.elapsed();

#ifdef _GENERATE_MARKDOWN
    std::cout << "| " << (100 - probability) << " | " << elapsed_flat.count() << " | " << elapsed_sparse.count() << " |" << std::endl;
#else
    std::cout << "----- N=" << N << ", probability: " << probability << ", number_order: " << number_order << " -----" << std::endl;
    std::cout << "Flat Matrix Multiplication: " << elapsed_flat.count()   << "ms" << std::endl;
    std::cout << "CRS  Matrix Multiplication: " << elapsed_sparse.count() << "ms" << std::endl;
    std::cout << std::endl;
#endif
}

int main()
{
    for (int i = 100; i >= 10; i -= 10) {
        run_benchmarks(1000, i, 10000);
    }

    return 0;
}
