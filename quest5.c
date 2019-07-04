
#include <pthread.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMTHREADS 8
#define PI 3.14159265358979323846
int main(){

	int nt = 10;
	int nx = 20; 
	float alpha = 0.1; 
	int L = 1; 
	float tmax = 0.5; 
	int errPlots=1; 
	float dx=L/(nx-1);
	float dt = tmax/(nt-1);
	float r = alpha*dt/(dx*dx); 
	float r2 = 1 - 2*r;
	float x[20];
	float t[10];
	float U[20][10] = {0};
	int i;
	for (i=0; i<20; i++){
		x[i] = i*0.0526;
	}

	for (i=0; i<10; i++){
		t[i] = i*0.0556;
	}

	for (i=0; i<20; i++){
		U[i][0] = sin(PI*x[i]/L);

	}
	int u0 = 0, uL = 0;

	double time= - omp_get_wtime();
	int m;
	#pragma omp parallel for private(i,m) shared(U) num_threads(NUMTHREADS)
    for (m=1; m<nt; m++){
    	for (i=1; i<nx-1; i++){
    		#pragma omp critical
    			 U[i][m] = r*U[i-1][m-1] + r2*U[i][m-1] + r*U[i+1][m-1];
       
    	}
	}
    time+=omp_get_wtime();
    printf("%f segundos \n",time);

}