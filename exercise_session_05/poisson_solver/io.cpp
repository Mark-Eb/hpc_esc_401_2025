#include "io.h"
#include "init.h"

/**
 * @brief      Output the exact solution to the Poisson equation in a csv file
 *
 * @param[in]  p        Parameters
 * @param      f        Matrix containing the source term
 */
void output_source(params p, double** f){
    std::string file_name = "output/output_source.csv";
    std::ofstream ofs(file_name, std::ofstream::out | std::ofstream::trunc);
    for (int i=0; i<p.nx; i++){
        for (int j=0; j<p.ny; j++){
            ofs << f[i][j];
            if (j != p.ny-1)
                ofs <<',';
        } 
        ofs << '\n';
    }
    ofs.close();
}

/**
 * @brief      Output the approximate solution
 *
 * @param[in]  p      Parameters
 * @param[in]  step   The current number of Jacobi steps performed
 * @param      u_new  Matrix containing the approximate solution
 */
void output(params p, int step, double** u_new){
    std::string fnum = std::to_string(step);
    fnum.insert(fnum.begin(), 7 - fnum.length(), '0');
    std::string file_name = "output/output_" + fnum + ".csv";
    std::ofstream ofs(file_name, std::ofstream::out | std::ofstream::trunc);
    for (int i=0; i<p.nx; i++){
        for (int j=0; j<p.ny; j++){
            ofs << u_new[i][j];
            if (j != p.ny-1)
                ofs <<',';
        } 
        ofs << '\n';
    }
    ofs.close();
}
