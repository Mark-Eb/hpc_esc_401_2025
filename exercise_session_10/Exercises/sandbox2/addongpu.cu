#include <cuda.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Define the matrix size */
#define NX 200
#define NY 100

/* Size of a block */
#define BLOCKSIZE 256

__global__ void kernadd (float* mout, float* min1, float *min2, int nx, int ny)
{
  int i, j, index;
  index = blockDim.x*blockIdx.x+threadIdx.x;
  j = index/nx;
  i = index - j*nx;
  if ((i < nx) && (j < ny))
    mout[index] = min1[index] + min2[index];
    
}


/*******************************************************/
/*  We initialize the vectors with random values       */
/*******************************************************/

void Init(float* mat, int nx, int ny) {
  int i, j;
  for (i = 0; i < nx; i++) {	/* 2D loop */
    for (j = 0; j < ny; j++) {
      mat[i+j*nx] = drand48 ();	/* position of cell (i,j) */
    }
  }
}


/*******************************************************/
/*            MAIN PROGRAM                             */
/*******************************************************/

int main () {
  int i=0, error=0, nx=NX, ny=NY;
  float diff;

  /* Matrix allocation */
  float *mat_in1 = (float*) malloc(nx * ny * sizeof(float));
  float *mat_in2 = (float*) malloc(nx * ny * sizeof(float));
  float *mat_out = (float*) malloc(nx * ny * sizeof(float));

  /* Matrix allocation on device */
  float *mat_out_gpu, *mat_in1_gpu, *mat_in2_gpu;
  /* TO DO : do the allocation below, using cudaMalloc()*/
  

  /* Matrix initialization */
  Init(mat_in1, nx, ny);
  Init(mat_in2, nx, ny);  
  
  /* TO DO : write below the instructions to copy it to the device */

  
  /* TO DO : complete the number of blocks below */
  int numBlocks = ...;
 
  /* TO DO : kernel invocation */
  
  
  cudaDeviceSynchronize();
  
  /* We now transfer back the matrix from the device to the host */
  /* TO DO : write cudaMemcpy() instruction below */
  
    
  /* free memory */
  cudaFree(mat_out_gpu);
  cudaFree(mat_in1_gpu);
  cudaFree(mat_in2_gpu);

  /* We now check that the result is correct */

  for (i=0; i< nx*ny; i++) {	/* No need for a 2D loop, actually ! */
    diff = mat_out[i] - (mat_in1[i]+mat_in2[i]);
    if (fabs(diff) > 0.0000001f) {
      error = 1;
    }
  }

  if (error) {
    printf("FAILED\n");
  }
  else {
    printf("PASSED\n");
  }
  free (mat_in1);
  free (mat_in2);
  free (mat_out);
}



