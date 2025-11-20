#include <cuda.h>
#include <stdio.h>

__global__ void add(int *a, int *b, int *c, int n) {
	int index = threadIdx.x+blockIdx.x*blockDim.x;
	if(index < n)
		c[index] = a[index] + b[index];
}

#define N 9
#define M 5

void random_ints(int* x, int size)
{
	int i;
	for (i=0;i<size;i++) {
		x[i]=rand()%10;
	}
}

int main(void) {
	int *a1, *b1, *c1, *a2, *b2, *c2;	// host copies of a, b, c
	int *a1_d, *b1_d, *c1_d, *a2_d, *b2_d, *c2_d;	// device copies of a, b, c
	int size = N * sizeof(int);
    
    cudaStream_t stream1,stream2;
    cudaError_t  error;
    error = cudaStreamCreate(&stream1);
    error = cudaStreamCreate(&stream2);

	// Alloc space for device copies of a, b, c
	cudaMalloc((void **)&a1_d, size);
	cudaMalloc((void **)&b1_d, size);
    cudaMalloc((void **)&c1_d, size);
    cudaMalloc((void **)&a2_d, size);
	cudaMalloc((void **)&b2_d, size);
	cudaMalloc((void **)&c2_d, size);

	// Alloc space for host copies of a, b, c and setup input values
	a1 = (int *)malloc(size); random_ints(a1, N);
    b1 = (int *)malloc(size); random_ints(b1, N);
    c1 = (int *)malloc(size);
    a2 = (int *)malloc(size); random_ints(a2, N);
    b2 = (int *)malloc(size); random_ints(b2, N);
    c2 = (int *)malloc(size);


	// Copy inputs to device
	cudaMemcpyAsync(a1_d, a1, size, cudaMemcpyHostToDevice, stream1);
    cudaMemcpyAsync(b1_d, b1, size, cudaMemcpyHostToDevice, stream1);
    
    cudaMemcpyAsync(a2_d, a2, size, cudaMemcpyHostToDevice, stream2);
	cudaMemcpyAsync(b2_d, b2, size, cudaMemcpyHostToDevice, stream2);

	// Launch add() kernel on GPU
    add<<<(N+M-1)/M,M,0,stream1>>>(a1_d, b1_d, c1_d,N);
    add<<<(N+M-1)/M,M,0,stream2>>>(a2_d, b2_d, c2_d,N);

	// Copy result back to host
    cudaMemcpyAsync(c1, c1_d, size, cudaMemcpyDeviceToHost, stream1);
    cudaMemcpyAsync(c2, c2_d, size, cudaMemcpyDeviceToHost, stream2);
        
    /*error=cudaStreamSynchronize(stream1);
    // Print results
    for(int i=0; i<N; i++)printf("stream1 %d + %d = %d\n",a1[i],b1[i],c1[i]);
    
    error=cudaStreamSynchronize(stream2);
    // Print results
	for(int i=0; i<N; i++)printf("stream2 %d + %d = %d\n",a2[i],b2[i],c2[i]);
    */

    cudaDeviceSynchronize();
    for(int i=0; i<N; i++)printf("stream1 %d + %d = %d\t stream2 %d + %d = %d\n",a1[i],b1[i],c1[i],a2[i],b2[i],c2[i]);
    if (error != 0) {
        printf ("%s\n", cudaGetErrorString (error));
        exit (1);
    }
        	
    // Cleanup
    free(a1); free(b1); free(c1);
    free(a2); free(b2); free(c2);
    cudaFree(a1_d); cudaFree(b1_d); cudaFree(c1_d);
    cudaFree(a2_d); cudaFree(b2_d); cudaFree(c2_d);
	return 0;
}
