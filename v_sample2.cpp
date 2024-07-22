// #include <iostream>
// #include <Eigen/Dense>
// #include <chrono>

// using namespace std;
// using namespace Eigen;

// int main() {
//     int size = 1500;

//     // Initializing matrices with 1 for simplicity
//     MatrixXi mat1 = MatrixXi::Ones(size, size);
//     MatrixXi mat2 = MatrixXi::Ones(size, size);
//     MatrixXi result(size, size);

//     auto start = chrono::high_resolution_clock::now();

//     result = mat1 * mat2;

//     auto end = chrono::high_resolution_clock::now();
//     chrono::duration<double> duration = end - start;

//     cout << "Matrix multiplication completed in " << duration.count() << " seconds." << endl;

//     return 0;
// }
#include <iostream>
#include <vector>
#include <chrono>
#include <immintrin.h> // Include for AVX intrinsics

using namespace std;

void multiplyMatrices(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2, vector<vector<int>>& result) {
    int rows1 = mat1.size();
    int cols1 = mat1[0].size();
    int cols2 = mat2[0].size();

    // Initialize the result matrix with zeros
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            result[i][j] = 0;
        }
    }

    // Matrix multiplication with AVX intrinsics
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; j += 8) { // Process 8 elements at a time
            __m256i c = _mm256_setzero_si256();
            for (int k = 0; k < cols1; ++k) {
                __m256i a = _mm256_set1_epi32(mat1[i][k]);
                __m256i b = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mat2[k][j]));
                __m256i prod = _mm256_mullo_epi32(a, b);
                c = _mm256_add_epi32(c, prod);
            }
            _mm256_storeu_si256(reinterpret_cast<__m256i*>(&result[i][j]), c);
        }
    }
}

int main() {
    int size = 1500;
    vector<vector<int>> mat1(size, vector<int>(size, 1)); // Initializing with 1 for simplicity
    vector<vector<int>> mat2(size, vector<int>(size, 1)); // Initializing with 1 for simplicity
    vector<vector<int>> result(size, vector<int>(size));

    auto start = chrono::high_resolution_clock::now();

    multiplyMatrices(mat1, mat2, result);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Matrix multiplication completed in " << duration.count() << " seconds." << endl;

    return 0;
}
