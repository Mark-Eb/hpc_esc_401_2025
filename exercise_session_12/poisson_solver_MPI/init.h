#ifndef INIT_H
#define INIT_H

#include <mpi.h>
#include <iostream>
#include <cmath>
struct params {
    // Which source term to use (1 or 2)
    int rhs_function;
    // Number of rows
    int nx;
    // Number of columns
    int ny;
    // Output frequency
    int foutput;
    // Maximum number of steps
    int nstep_max;
    // Tolerance for the Jacobi algorithm
    double tol;
    // process' domain 
    int xmin,xmax,ymin,ymax;
    // process' neighbours 
    int left_rank, right_rank, top_rank, bottom_rank;
    // group for synchronous split communication
    int my_group;
    // domain decomposition
    //      1: simple slabs
    //      2: balanced slabs
    //      3: cartesian
    // int domain_decomposition;
    // communication method 
    //      1: odd/even process groups
    //      2: non-blocking, 
    //      3: non-blocking hiding computation
    // number of processes in x-dim (cartesian topology)
    int nproc_x;
    // number of processes in y-dim (cartesian topology)
    int nproc_y;

    int communication;

    MPI_Comm comm;
};

void readParameters(const char*, params*);

double** allocateGrid(int nx, int ny, double** M);
double source_term(double x, double y, int function);
double exact_solution(double x, double y, int function);
double boundary(double x, double y, int function);

void init_f(params p, double **f);
void init_variables(params p, double **f, double **u_old, double **u_new);

#endif
