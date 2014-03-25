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

int checkEqual(double *a, double *b, int n) {
  int i, j;
  for (i = 0; i < n*n; i++)
    if (abs(a[i] - b[i]) > 0.00001)
      return -1;
  return 0;
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
  assignIdentity(u, n);

  memcpy(b, a, n*n*sizeof(double));

  int c, r;
  for (c = 0; c < n-1; c++)
    for (r = n-2; r > c; r--) {
      double x = b[r*n+c];
      double y = b[(r+1)*n+c];
      double sina = -y/sqrt(x*x+y*y);
      double cosa = x/sqrt(x*x+y*y);

      // b[r*n+c] = cosa*x - sina*y;
      // b[(r+1)*n+c] = 0;

      // double *v = (double *)malloc(n*n*sizeof(double));
      // double *vt = (double *)malloc(n*n*sizeof(double));
      // assignIdentity(v, n);
      // v[r*n+r] = cosa;
      // v[r*n+r+1] = -sina;
      // v[(r+1)*n+r] = sina;
      // v[(r+1)*n+r+1] = cosa;

      // memcpy(vt, v, n*n*sizeof(double));
      // transpose(vt, n);


      // printf("B:\n");
      // printMatrix(b, n);
      // printf("V:\n");
      // printMatrix(v, n);
      // printf("VT:\n");
      // printMatrix(vt, n);

      // printf("U:\n");
      // printMatrix(u, n);

      // memcpy(b, multiply(b, vt, n, n, n), n*n*sizeof(double));
            
      //update b
      int j = 0;
      for (j = 0; j < n; j++) {
	double b_rj = b[r*n+j];
	double b_r1j = b[(r+1)*n+j];
	b[r*n+j] = cosa * b_rj - sina * b_r1j;
	b[(r+1)*n+j] = sina * b_rj + cosa * b_r1j;

	
	//update u
	double u_rj = u[r*n+j];
	double u_r1j = u[(r+1)*n+j];
	u[r*n+j] = cosa * u_rj - sina * u_r1j;
	u[(r+1)*n+j] = sina * u_rj + cosa * u_r1j;


      }
      for (j = 0; j < n; j++) {
	double b_jr = b[j*n+r];
	double b_jr1 = b[j*n+r+1];
	b[j*n+r] = cosa*b_jr - sina*b_jr1;
	b[j*n+r+1] = sina*b_jr + cosa*b_jr1;
      }



      //update U
      /*double *v = (double *)malloc(n*n*sizeof(double));
      assignIdentity(v, n);
      v[r*n+r] = cosa;
      v[r*n+r+1] = -sina;
      v[(r+1)*n+r] = sina;
      v[(r+1)*n+r+1] = cosa;            
      memcpy(u, multiply(v, u, n, n, n), n*n*sizeof(double));
      */
      // printf("\nV:\n");
      // printMatrix(v, n);

      // printf("\nB:\n");
      // printMatrix(b, n);
      // printf("U:\n");
      // printMatrix(u, n);

      //getchar();


    }

  return;
}

int problem(int n) {
  srand(time(NULL));
  
  int i, j;

  double *a = (double *)malloc(n*n*sizeof(double));
  double *u = (double *)malloc(n*n*sizeof(double));
  double *b = (double *)malloc(n*n*sizeof(double));


  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      a[i*n+j] = (double)rand()/(double)RAND_MAX * 10;
      //a[j*n+i] = a[i*n+j];
    }


  //double a[25] = {5,1,2,0,4,1,4,2,1,3,2,2,5,4,0,0,1,4,1,3,4,3,0,3,4};



  printf("Original A:\n");
  printMatrix(a, n);  
  printf("\n\n");


  upperhes(a, n, u, b);


  int ucheck = -1;
  int bcheck = -1;


  double *ut = (double *)malloc(n*n*sizeof(double));
  memcpy(ut, u, n*n*sizeof(double));
  transpose(ut, n);
    


  printf("\n\n\nResult U:\n");
  printMatrix(u, n);

  printf("Verifying U:\n");
  printMatrix(multiply(u, ut, n, n, n), n);
  double *id = (double *)malloc(n*n*sizeof(double));
  assignIdentity(id, n);
  if (checkEqual(multiply(u, ut, n, n, n), id, n) == 0) {
    printf("U Correct!\n");
    ucheck = 0;
  }



  printf("\nResult B:\n");
  printMatrix(b, n);
  printf("Verifying B:\n");
  printMatrix(multiply(multiply(u, a, n, n, n), ut, n, n, n), n);
  if (checkEqual(multiply(multiply(u, a, n, n, n), ut, n, n, n), b, n) == 0) {
    printf("B Correct!\n\n");
    bcheck = 0;
  }

  if (ucheck == -1 || bcheck == -1)
    return -1;
  return 0;
}

int main() {
  srand(time(NULL));

  int i;
  for (i = 0; i < 1000; i++) {
    int n = rand() % 10 + 3;
    if (problem(n) != 0) {
      printf("Error!!!");
      break;
    }
    printf("Round %d\n", i);
  }

  return 0;
}




