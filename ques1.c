#include <pthread.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/* Define length of dot product vectors and number of OpenMP threads */
#define VECLEN 9999999
#define NUMTHREADS 16

int main (int argc, char* argv[])
{
int i, tid, len=VECLEN, threads=NUMTHREADS;
double *a, *b;
double sum, psum;

/* Assign storage for dot product vectors */
a = (double*) malloc (len*threads*sizeof(double));
b = (double*) malloc (len*threads*sizeof(double));
 

for (i=0; i<len*threads; i++) {
  a[i]=1.0;
  b[i]=a[i];
  }
sum = 0.0;


double time= - omp_get_wtime();
#pragma omp parallel private(i,tid,psum) num_threads(threads) 
{
psum = 0.0;
tid = omp_get_thread_num();

#pragma omp for reduction(+:sum)
  for (i=0; i<len*threads; i++) 
    {
    	//printf("\n%d\n", omp_get_wtime());
      sum += (a[i] * b[i]);
      psum = sum;
    }

time+=omp_get_wtime();
printf("%f segundos \n",time);

free (a);
free (b);
}