#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <omp.h>

using namespace std;
using namespace std::chrono;

const int N = 1000;

int A[N][N], B[N][N], C[N][N];

void init_matrix(int mat[][N])
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            mat[i][j] = dist(gen);
        }
    }
}

void matrix_multiply()
{
#pragma omp parallel for
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    init_matrix(A);
    init_matrix(B);
    auto start_time = high_resolution_clock::now();

    matrix_multiply();

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);

    ofstream fout("output.txt");
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            fout << C[i][j] << " ";
        }
        fout << "\n";
    }
    fout.close();
    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    return 0;
}
