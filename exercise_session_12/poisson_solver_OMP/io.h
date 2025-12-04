#ifndef IO_H
#define IO_H

#include "init.h"
#include <fstream>

void output_source(params p, double** f);
void output(params p, int step, double** u_new);

#endif