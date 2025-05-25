
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

int main() {
    const int N = 500;
    vector<vector<int>> A(N, vector<int>(N, 1));
    vector<vector<int>> B(N, vector<int>(N, 2));
    vector<vector<int>> C(N, vector<int>(N, 0));

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Execution Time: " << duration.count() << " seconds" << endl;
    return 0;
}
