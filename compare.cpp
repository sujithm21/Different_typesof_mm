#include <iostream>
#include <vector>
#include <chrono>
#include <immintrin.h>

using namespace std;

void multiplyMatrices(const vector<vector<float>> &mat1, const vector<vector<float>> &mat2, vector<vector<float>> &result)
{
    int rows1 = mat1.size();
    int cols1 = mat1[0].size();
    int cols2 = mat2[0].size();

    // Initialize the result matrix with zeros
    for (int i = 0; i < rows1; ++i)
    {
        for (int j = 0; j < cols2; ++j)
        {
            result[i][j] = 0;
        }
    }

    // Matrix multiplication with AVX intrinsics
    for (int i = 0; i < rows1; ++i)
    {
        for (int j = 0; j < cols2; ++j)
        {
            __m256 sum = _mm256_setzero_ps(); // Initialize a vector register to hold partial sums
            for (int k = 0; k < cols1; k += 8)
            {
                int limit = (k + 8 > cols1) ? cols1 - k : 8;

                // Load elements from mat1 and mat2
                __m256 a = _mm256_loadu_ps(&mat1[i][k]); // Load 8 elements from mat1
                __m256 b = _mm256_setzero_ps();
                for (int l = 0; l < limit; ++l)
                {
                    b[l] = mat2[k + l][j]; // Manually load elements from mat2
                }

                sum = _mm256_fmadd_ps(a, b, sum); // Perform Fused Multiply-Add operation
            }
            float temp[8];
            _mm256_storeu_ps(temp, sum);                                                                  // Store the result back to memory
            result[i][j] = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7]; // Sum the partial results
        }
    }
}

int main()
{
    int size = 1500;
    vector<vector<float>> mat1(size, vector<float>(size, 1.0f)); // Initializing with 1.0f for simplicity
    vector<vector<float>> mat2(size, vector<float>(size, 1.0f)); // Initializing with 1.0f for simplicity
    vector<vector<float>> result(size, vector<float>(size));

    auto start = chrono::high_resolution_clock::now();

    multiplyMatrices(mat1, mat2, result);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Matrix multiplication completed in " << duration.count() << " seconds." << endl;

    return 0;
}