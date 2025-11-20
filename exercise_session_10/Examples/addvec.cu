#include <cuda.h>
#include <stdio.h>

__global__ void add(int *a, int *b, int *c) {
	int index = blockIdx.x;
	c[index] = a[index] + b[index];
}

#define N 512

void random_ints(int* x, int size)
{
	int i;
	for (i=0;i<size;i++) {
		x[i]=rand()%10;
	}
}

int main(void) {
	int *a, *b, *c;	// host copies of a, b, c
	int *a_d, *b_d, *c_d;	// device copies of a, b, c
	int size = N * sizeof(int);
	
	// Alloc space for device copies of a, b, c
	cudaMalloc((void **)&a_d, size);
	cudaMalloc((void **)&b_d, size);
	cudaMalloc((void **)&c_d, size);

	// Alloc space for host copies of a, b, c and setup input values
	a = (int *)malloc(size); random_ints(a, N);
	b = (int *)malloc(size); random_ints(b, N);
	c = (int *)malloc(size);

	// Copy inputs to device
	cudaMemcpy(a_d, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(b_d, b, size, cudaMemcpyHostToDevice);

	// Launch add() kernel on GPU
	add<<<N,1>>>(a_d, b_d, c_d);
	
	// Copy result back to host
	cudaMemcpy(c, c_d, size, cudaMemcpyDeviceToHost);
		
    // Print results
	for(int i=0; i<N; i++)printf("%d) %d + %d = %d\n",i,a[i],b[i],c[i]);
        	
    // Cleanup
    free(a); free(b); free(c);
	cudaFree(a_d); cudaFree(b_d); cudaFree(c_d);
	return 0;
}
