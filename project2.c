#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

void printMatrix(double *a, int n) {
  printf("***************** Matrix %d x %d *********************\n", n, n);
  int i = 0;
  for (i = 0; i < n * n; ++i) {
    printf("%8.5f ", a[i]);
    if ((i+1) % n == 0)
      printf("\n");
  }
  return;
}

void transpose(double *a, int n) {
  int i, j;
  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      double tmp = a[i*n + j];
      a[i*n + j] = a[j*n + i];
      a[j*n + i] = tmp;
    }
  }
  return;
}

double* multiply(double *a, double *b, int p, int q, int r) {
  double *result = (double*)malloc(p*r*sizeof(double));
  int i, j, k;
  for (i = 0; i < p; i++) {
    for (j = 0; j < r; j++) {
      double sum = 0;
      for (k = 0; k < q; k++)
        sum += a[i*q+k] * b[k*r+j];
      result[i*r+j] = sum;
    }
  }
  return result;
}
void assignIdentity(double *a, int n) {
  int r, c;
  for (r = 0; r < n; ++r) {
    for (c = 0; c < n; ++c) {
      if (r == c)
	a[r*n+c] = 1;
      else
	a[r*n+c] = 0;
    }
  }
  return;
}

void upperhes(double *a, int n, double *u, double *b) {
  memcpy(u, a, n*n*sizeof(double));
  

}

void problem(int n) {
  srand(time(NULL));
  
  int i, j;

  double *a = (double *)malloc(n*n*sizeof(double));
  double *u = (double *)malloc(n*n*sizeof(double));
  double *b = (double *)malloc(n*n*sizeof(double));

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      a[i*n+j] = (double)rand()/(double)RAND_MAX * 10;
  
  upperhes(a, n, u, b);

}

int main() {
  problem(5);
  return 0;
}




