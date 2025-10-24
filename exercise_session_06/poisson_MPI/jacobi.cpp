#include "jacobi.h"
#include <math.h>
#include "mpi_module.h"

/**
 * @brief      Computes norm of the difference between two matrices
 *
 * @param[in]  p     Parameters
 * @param      mat1  The matrix 1
 * @param      mat2  The matrix 2
 *
 * @return     Returns \sqrt{\sum(mat1_{ij} - mat2_{ij})^2/(nx*ny)}
 */
double norm_diff(params p, double** mat1, double** mat2){

    printf("Here, in norm_diff() function, change the serial implementation to MPI setup\n");
    double ret=0., diff=0.;
    for (int i=0; i<p.nx; i++){
        for (int j=0; j<p.ny; j++){
            diff = mat1[i][j] - mat2[i][j];
            ret += diff*diff;
        }
    }
    ret = sqrt(ret/(p.nx*p.ny));
    return ret;
}

/**
 * @brief      Compute a Jacobi iteration to solve Poisson equation. This function updates
 *             u_new and u_old in-place.
 *
 * @param[in]  p      Parameters
 * @param      u_new  The new solution
 * @param      u_old  The old solution
 * @param      f      The source term
 */
void jacobi_step(params p, double** u_new, double** u_old, double** f, int my_rank, int size){
    double dx = 1.0/((double)p.nx - 1);
    double dy = 1.0/((double)p.ny - 1);

    double* fromLeft = new double[p.ymax - p.ymin]; 
    double* fromRight = new double[p.ymax - p.ymin];

    for (int i=p.xmin; i<p.xmax; i++){
        for (int j=p.ymin; j<p.ymax; j++){
            u_old[i - p.xmin][j - p.ymin] = u_new[i - p.xmin][j - p.ymin];
        }
    }

    halo_comm(p, my_rank, size, u_new, fromLeft, fromRight); 

    printf("Function jacobi_step in jacobi.cpp : adapt the update of u_new.\n");
    for (int i=p.xmin; i<p.xmax; i++){
        if (i==0 || i==p.nx-1) continue;
        for (int j=p.ymin; j<p.ymax; j++){
            if (j==0 || j==p.ny-1) continue;
            int idx = i-p.xmin;
            int idy = j-p.ymin;
            u_new[idx][idy] = 0.25*(u_old[idx-1][idy] + u_old[idx+1][idy] + u_old[idx][idy-1] + u_old[idx][idy+1] - dx*dy*f[idx][idy]);
        }
    }
    if (p.nx!=p.ny) printf("In function jacobi_step (jacobi.cpp l.26): nx != ny, check jacobi updates\n");
}
