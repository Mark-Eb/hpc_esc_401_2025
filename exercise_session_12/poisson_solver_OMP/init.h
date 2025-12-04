#ifndef INIT_H
#define INIT_H
#include <cmath>
#include <iostream>

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
};

void readParameters(const char*, params*);

double** allocateGrid(int nx, int ny, double** M);
double source_term(double x, double y, int function);
double exact_solution(double x, double y, int function);
double boundary(double x, double y, int function);

void init_f(params p, double **f);
void init_variables(params p, double **f, double **u_old, double **u_new);

#endif
