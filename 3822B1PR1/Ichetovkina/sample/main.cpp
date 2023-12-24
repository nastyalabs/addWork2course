#include <iostream> 
#include<vector> 
#include<random>
#include<chrono>
#include"Header.h"

using namespace std;
double test_CRSMatrix(int tests, int size, int freq) {
    double time = 0.0;
    for (size_t i = 0; i < tests; i++) {
        CRS A(size, freq), B(size, freq);
        auto start = chrono::steady_clock::now();
        A* B;
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        time += chrono::duration<double, milli>(diff).count();
    }
    return time / tests;
}
int main() {

    // Ìàòğèöà êàê ÂÅÊÒÎĞ İËÅÌÅÍÒÎÂ

    int n = 2;
    cout << "Matrix as a vector of elements: \n";
    cout << "v1 = { 1,2, 3,4 }\n";
    cout << "v2 = { 3,4, 3,2 }" << endl;
    vector<int> v1 = { 1,2, 3,4 };
    vector<int> v2 = { 3,4, 3,2 };
    vector<int> v3(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            v3[i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                v3[i * n + j] += v1[i * n + k] * v2[k * n + j];
                //cout << v3[i * n + j] << endl; 
            }
        }
    }
    for (int i = 0; i < (n * n); i+=2) {
        cout << v3[i] <<"  "<<v3[i+1]<< endl;
    }



    // Ìàòğèöà êàê ÂÅÊÒÎĞ ÂÅÊÒÎĞÎÂ
    cout << "\n\nMatrix as a vector of vectors: \n";
    cout << "vec1 = { {1,2},{4,5} }\n";
    cout << "vec2 = { {1,2},{3,1} }\n";
    vector<vector<int>> vec1 = { {1,2},{4,5} };
    vector<vector<int>> vec2 = { {1,2},{3,1} };
    vector<vector<int>> vec3 = {{0,0},{0,0}};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                vec3[i][j] = vec1[i][k] * vec2[k][j];
            }
        }
    }
    cout << "vec3: \n";
    for (int i = 0;i < n;i++) {
        cout << "    ";
        for (int j = 0; j < n;j++) {
            cout << vec3[i][j]<<"   ";
        }
        cout << "\n";

    }
    // CRS matrix
    cout << "CRS Matrix" << endl;
    for (auto size : { 100, 500, 1000, 1500, 2000 }) {
        for (int freq : {2}) {
            cout << "size: " << size << ", frequency = "<<freq<< endl;
            cout << "Takes: " << test_CRSMatrix(1, size, freq) << " ms.";
            cout << "\n\n";
        }
    }


    return 0;
}