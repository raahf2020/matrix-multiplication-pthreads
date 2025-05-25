
#include <iostream>
#include <vector>
#include <pthread.h>
#include <chrono>
using namespace std;

int N = 500;
vector<vector<int>> A(N, vector<int>(N, 1));
vector<vector<int>> B(N, vector<int>(N, 2));
vector<vector<int>> C(N, vector<int>(N, 0));

struct ThreadData {
    int startRow, endRow;
};

void* multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->startRow; i < data->endRow; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return nullptr;
}

int main() {
    int numThreads = 4;
    pthread_t threads[numThreads];
    ThreadData td[numThreads];
    int rowsPerThread = N / numThreads;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < numThreads; ++i) {
        td[i].startRow = i * rowsPerThread;
        td[i].endRow = (i == numThreads - 1) ? N : (i + 1) * rowsPerThread;
        pthread_create(&threads[i], nullptr, multiply, &td[i]);
    }

    for (int i = 0; i < numThreads; ++i)
        pthread_join(threads[i], nullptr);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Execution Time: " << duration.count() << " seconds" << endl;
    return 0;
}
