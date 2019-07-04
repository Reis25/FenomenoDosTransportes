
#include <pthread.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 500
#define NUMTHREADS 64

int A[N][N];
int B[N][N];
int C[N][N];

int main(int argc, char* argv[]) 
{
    int i,j,k;
    for (i= 0; i< N; i++){
        for (j= 0; j< N; j++){
            A[i][j] = 2;
            B[i][j] = 2;
         }       
    }

    double time= - omp_get_wtime();
    #pragma omp parallel for private(i,j,k) shared(A,B,C) num_threads(NUMTHREADS)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    time+=omp_get_wtime();
    printf("%f segundos \n",time);

}