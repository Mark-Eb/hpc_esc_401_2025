#!/bin/bash -l

sbatch --cpus-per-task=$1 --output=poisson_omp_$1_$2.out run_argv.job params_${2}.txt 

