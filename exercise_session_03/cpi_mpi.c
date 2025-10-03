#include <stdio.h>
#include "mpi.h"

static long nSteps = 1000000000;
static double PI25DT = 3.141592653589793238462643;

int main(int argc, char** argv){
    int n, myRank, nProcs;
    long i;
    double mypi, pi, h, sum, x;
    double tWStart, tWElapsed;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

    printf("Process rank: %d\n", myRank);
  
	h   = 1.0 / (double) nSteps;
	sum = 0.0;

    tWStart = MPI_Wtime();

	for (i = myRank ; i < nSteps; i += nProcs) {
	    x = h * ((double)i - 0.5);
	    sum += 4.0 / (1.0 + x*x);
	}
	mypi = h * sum;
    
	MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
		   MPI_COMM_WORLD);
    
    tWElapsed = MPI_Wtime() - tWStart;
	if (myRank == 0){
	    printf("pi is approximately %.16f, Error is %.16f\n",
		        pi, pi - PI25DT);
        printf("Computed in %.4g seconds\n", tWElapsed);
    }
    MPI_Finalize();
    return 0;
}
