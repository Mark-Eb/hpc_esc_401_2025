#include "init.h"
#include <math.h>
/**
 * @brief      Reads parameters and update the params structure
 *
 * @param[in]  file_name  The parameter file name
 * @param      param      The parameter structure
 */
void readParameters(const char* file_name, params *param) {
    FILE *fp;
    fp = std::fopen(file_name, "r");

    if (fp==NULL) perror ("Error opening file");
    char line[256];

    printf("Reading parameters:\n");
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "nx=%d\n", &param->nx)) 
            printf("\t nx=%d\n", param->nx);
        if (sscanf(line, "ny=%d\n", &param->ny))
            printf("\t ny=%d\n", param->ny);
        if (sscanf(line, "foutput=%d\n", &param->foutput))
            printf("\t foutput=%d\n", param->foutput);
        if (sscanf(line, "nstep_max=%d\n", &param->nstep_max))
            printf("\t nstep_max=%d\n", param->nstep_max);
        if (sscanf(line, "tolerance=%lg\n", &param->tol))
            printf("\t tolerance=%lg\n", param->tol);
        if (sscanf(line, "rhs_function=%d\n", &param->rhs_function))
            printf("\t rhs_function=%d\n", param->rhs_function);
    }
    fclose(fp);
}

/**
 * @brief      Dynamic allocation of matrix
 *
 * @param[in]  nx    Number of rows
 * @param[in]  ny    Number of columns
 * @param      M     Matrix to initialize
 *
 * @return     Returns the allocated matrix
 */
double** allocateGrid(int nx, int ny, double** M){
    M = new double *[nx];
    for (int i = 0; i < nx; i++){
        M[i] = new double[ny];
    }
    return M;
}

/**
 * @brief      Compute the source term at a given location
 *
 * @param[in]  x         The x position
 * @param[in]  y         The y position
 * @param[in]  rhs_function  The type of source term to be used (1 or 2)
 *
 * @return     Returns the value of the source term at position (x,y)
 */
double source_term(double x, double y, int rhs_function){
    double ret = 0;
    if(rhs_function==1)
        ret = 8*M_PI*M_PI * sin(2.0*M_PI*x) * sin(2.0*M_PI*y);
    else if (rhs_function==2)
        ret = 0;
    return ret;
}

/**
 * @brief      Compute the boundary conditions at the edges of the domain
 *
 * @param[in]  x         The x position
 * @param[in]  y         The y position
 * @param[in]  rhs_function  The type of source term to be used (1 or 2)
 *
 * @return     Returns the boundary condition of the Poisson problem.
 */
double boundary(double x, double y, int rhs_function){
    if (rhs_function==1) 
        return 0.0;

    else if (rhs_function==2){
        if (x<0.75 && x>0.25 && y==0.) return 1.0;
        else return 0.0;
    }
    return 0.0;
}

/**
 * @brief      Initialize the source term
 *
 * @param[in]  p     Parameters
 * @param      f     Matrix containing the source term
 *                   The "boundary" entries of f store the boundary values of the solution
 *                   The "interior" entries of f store the source term of Poisson eq.
 */
void init_f(params p, double **f){
    // printf("Function init_f (init.cpp l.97): not implemented.\n");
    double dx=1/((double)p.nx-1), dy=1/((double)p.ny-1);
    for (int i=p.xmin;i<p.xmax;i++)
        for (int j=p.ymin; j<p.ymax;j++)
        {
            if (i==0 || j==0 || i==p.nx-1 || j==p.ny - 1)
            {
                f[i - p.xmin][j - p.ymin] = boundary(i*dx,j*dy,p.rhs_function);    
            }
            else
            {
                f[i - p.xmin][j - p.ymin] = source_term(i*dx,j*dy,p.rhs_function);    
            }            
        }
}

/**
 * @brief      Initializes the matrices used in the Jacobi iteration
 *
 * @param[in]  p        Parameters
 * @param      f        { parameter_description }
 * @param      u_old    Matrix containing the old solution
 * @param      u_new    Matrix containing the new solution
 */
void init_variables(params p, double **f, double **u_old, double **u_new){
    init_f(p, f);
    for (int i=0; i<(p.xmax - p.xmin); i++){
        for (int j=0; j<(p.ymax - p.ymin); j++){
            u_old[i][j]  = f[i][j];
            u_new[i][j]  = f[i][j];
        }
    }
}
