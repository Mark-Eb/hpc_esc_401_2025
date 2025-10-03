#include <stdio.h>
#include <sys/time.h>

static long nSteps = 1000000000;
static double PI25DT = 3.141592653589793238462643;

double getTime(void) {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return tv.tv_sec + 1e-6*(double)tv.tv_usec;
}

int main(int argc, char** argv){
    double pi, h, sum, x;
    double tStart, tElapsed;

	h   = 1.0 / (double) nSteps;
	sum = 0.0;
    tStart = getTime();

	for (long i = 0 ; i < nSteps; i ++) {
	    x = h * ((double)i - 0.5);
	    sum += 4.0 / (1.0 + x*x);
	}
	pi = h * sum;
    
    tElapsed = getTime() - tStart;
	printf("pi is approximately %.16f, Error is %.16f\n",
		        pi, pi - PI25DT);
    printf("Computed in %.4g seconds\n", tElapsed);
    return 0;
}
