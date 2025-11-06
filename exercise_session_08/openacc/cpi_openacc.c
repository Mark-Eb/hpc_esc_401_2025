#include <stdio.h> 
#include "gettime.h"

static long steps = 1000000000;

int main (int argc, const char *argv[]) {
    int i; double x;
    double pi;
    double step = 1.0/(double) steps;
    for (int j=0;j<5;j++){
        double sum = 0.0;
        double start = getTime();
        for (i=0; i < steps; i++) {
            x = (i+0.5)*step;
            sum += 4.0 / (1.0+x*x);
        }
        pi = step * sum;
        double delta = getTime() - start;
        printf("PI = %.16g computed in %.4g seconds\n", pi, delta);
    }
}

