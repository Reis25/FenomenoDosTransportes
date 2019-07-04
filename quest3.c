
#include <pthread.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


#define N 100000
#define NUMTHREADS 1

float phiNew[N];
float phiOld[N];

int main(int argc, char* argv[]) 
{
    int tmax = 5000;

    float alpha=1,dt=0.005,dx=0.05;
    float r = alpha*dt / ( dx*dx );
    double time= - omp_get_wtime();
    int i,t;
    #pragma omp parallel for private(i,t) shared(phiNew,phiOld) num_threads(NUMTHREADS)
    for (t = 0; t < tmax; t++) {
        for (i = 0; i <= N; i++) {
               phiNew[i] = phiOld[i] + r*(phiOld[i+1] - 2*phiOld[i] + phiOld[i-1] );
            
        }
        
    }

    time+=omp_get_wtime();
    printf("%f segundos \n",time);

}