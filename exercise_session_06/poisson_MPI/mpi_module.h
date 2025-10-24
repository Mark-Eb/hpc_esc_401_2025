#ifndef MPI_MODULE
#define MPI_MODULE


// #include "init.h"

int start_MPI(int* my_rank, int* size);
int close_MPI();
int mpi_get_domain(int nx, int ny, int my_rank, int size, int* min_x, int* max_x, int* min_y, int* max_y);
int halo_comm(params p, int my_rank, int size, double** u, double* fromLeft, double* fromRight);
int ALLREDUCE(double* loc_diff, double* loc_sumdiff);

#endif