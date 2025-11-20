#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define STOP 0
#define START 1

#define N 1000 		/* Size of square matrix */

void gpu_convol (float *, float *, int);

/* (over-)Simple chronometer function */
void chrono (int kind, float *time) {
  static clock_t counts;
  if (kind == START) {
    *time = 0.0;
    counts = clock();
    return;
  }
  if (kind == STOP) {
    *time = ((float)(clock()-counts))/((float)CLOCKS_PER_SEC);
  }
}

void init (float *m, int n) {
  int i;
  for (i = 0; i < n*n; i++)
    m[i] = drand48();
}

void compare (float *a, float *b, int n) {
  int i, errors=0;
  for (i = 0; i < n*n; i++) {
    if (fabsf(a[i]-b[i]) > 1e-7) { //Play with this value to get an idea of the accuracy of your platform
      errors++;
    }
  }
  if (errors==0)
    printf ("PASSED\n");
  else
    printf ("FAILED: %d errors\n", errors);
}

void cpu_convol (float *a, float *b, int n) {
  int i, j, l;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      l = i*n+j;		/* 1D index */
      if ((i == 0) || (j == 0) || (i == n-1) || (j == n-1)) 
	      b[l] = a[l];
      else {/* Make sure you understand the indices below */
	      b[l]=(1./5.)*( a[l-n] +	a[l-1] + a[l] + a[l+1] + a[l+n] );
      }
    }
  }
}

int main () {
  float *a, *b, *c, time;
  int n = N;
  a = malloc (n*n*sizeof(float));
  b = malloc (n*n*sizeof(float));
  c = malloc (n*n*sizeof(float));
  init (a, n);
  gpu_convol (a, c, n);
  chrono (START, &time);
  cpu_convol (a, b, n);
  chrono (STOP, &time);
  printf ("Convolution took  %f sec. on CPU\n", time);
  compare (b, c, n);
  free (a);
  free (b);
  free (c);
}
