#include "io.h"
#include "init.h"
#include "jacobi.h"

#include <time.h>
int main (int argc, char *argv[]){

    double start,end;
    start = omp_get_wtime();
    //const char* file_name="params.txt";
    const char* file_name=argv[1];

    // Read the parameter file and store information in a params structure (defined in init.h)
    params p;
    readParameters(file_name, &p);

    // Initialize the matrices used in the Jacobi iteration
    double **f, **u_old, **u_new;

    // First allocate memory for each matrix
    f = allocateGrid(p.nx, p.ny, f);
    u_old = allocateGrid(p.nx, p.ny, u_old);
    u_new = allocateGrid(p.nx, p.ny, u_new);
    // Initialize the value of matrices
    init_variables(p, f, u_old, u_new);

    // Output the source term of the Poisson equation in a csv file
    output_source(p, f);

    // Do a first jacobi step
    jacobi_step(p, u_new, u_old, f);

    // Compute differences and norm
    double diff = norm_diff(p, u_new, u_old);

    // Initialize the Jacobi step conter
    int nstep=1;

    // Main loop for the Jacobi iterations
    while (diff>p.tol && nstep<p.nstep_max){
        jacobi_step(p, u_new, u_old, f);
        diff = norm_diff(p, u_new, u_old);
        nstep++;
        printf("Step %d, Diff=%g\n", nstep, diff);
        if (nstep%p.foutput==0) output(p, nstep, u_new);
    }
    //final output
    output(p, nstep, u_new);

    end = omp_get_wtime();
    double cpu_time = (double)(end - start);
    printf("Total ellapsed time: %.3g\n",cpu_time);
    return 0;
}
