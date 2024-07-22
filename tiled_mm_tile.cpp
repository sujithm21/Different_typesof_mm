#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int MATRIX_SIZE = 1500;

void initializeMatrix(vector<vector<int>>& matrix, int value) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = value;
        }
    }
}

void tiledMatrixMultiplication(const vector<vector<int>>& A,
                               const vector<vector<int>>& B,
                               vector<vector<int>>& C,
                               int tile_size) {
    for (int i = 0; i < MATRIX_SIZE; i += tile_size) {
        for (int j = 0; j < MATRIX_SIZE; j += tile_size) {
            for (int k = 0; k < MATRIX_SIZE; k += tile_size) {
                // Perform the multiplication on the current tile
                for (int ii = i; ii < i + tile_size && ii < MATRIX_SIZE; ++ii) {
                    for (int jj = j; jj < j + tile_size && jj < MATRIX_SIZE; ++jj) {
                        for (int kk = k; kk < k + tile_size && kk < MATRIX_SIZE; ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> A(MATRIX_SIZE, vector<int>(MATRIX_SIZE));
    vector<vector<int>> B(MATRIX_SIZE, vector<int>(MATRIX_SIZE));
    vector<vector<int>> C(MATRIX_SIZE, vector<int>(MATRIX_SIZE, 0));

    initializeMatrix(A, 1);
    initializeMatrix(B, 1);

    int tile_sizes[] = {120, 130, 140, 150, 160}; // Example tile sizes around the calculated optimal size

    for (int tile_size : tile_sizes) {
        // Reinitialize the result matrix for each test
        fill(C.begin(), C.end(), vector<int>(MATRIX_SIZE, 0));

        auto start = high_resolution_clock::now();

        tiledMatrixMultiplication(A, B, C, tile_size);

        auto stop = high_resolution_clock::now();
        chrono::duration<double> duration = stop - start;

        cout << "Matrix multiplication with tile size " << tile_size << " completed in " << duration.count() << " seconds." << endl;
    }

    return 0;
}
