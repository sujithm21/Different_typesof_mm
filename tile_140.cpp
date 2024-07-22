#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int MATRIX_SIZE = 1500;
const int TILE_SIZE = 140;

void initializeMatrix(vector<vector<int>>& matrix, int value) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = value;
        }
    }
}

void tiledMatrixMultiplication(const vector<vector<int>>& A,
                               const vector<vector<int>>& B,
                               vector<vector<int>>& C) {
    for (int i = 0; i < MATRIX_SIZE; i += TILE_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j += TILE_SIZE) {
            for (int k = 0; k < MATRIX_SIZE; k += TILE_SIZE) {
                // Perform the multiplication on the current tile
                for (int ii = i; ii < i + TILE_SIZE && ii < MATRIX_SIZE; ++ii) {
                    for (int jj = j; jj < j + TILE_SIZE && jj < MATRIX_SIZE; ++jj) {
                        for (int kk = k; kk < k + TILE_SIZE && kk < MATRIX_SIZE; ++kk) {
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

    auto start = high_resolution_clock::now();

    tiledMatrixMultiplication(A, B, C);

    auto stop = high_resolution_clock::now();
    chrono::duration<double> duration = stop - start;

    cout << "Matrix multiplication completed in " << duration.count() << " seconds." << endl;

    return 0;
}
