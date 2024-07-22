#include <iostream>
#include <vector>
#include <chrono>

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

    // Matrix multiplication with loop interchange
    for (int i = 0; i < rows1; ++i) {
        for (int k = 0; k < cols1; ++k) {
            for (int j = 0; j < cols2; ++j) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
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
