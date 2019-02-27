#ifndef HILBERT_H_
#define HILEBRT_H_

#include <stdlib.h>

struct point
{
    int x;
    int y;
};

typedef struct point point_t;

void hilbert_c(unsigned int degree,     // degree of hilbert curve
               unsigned int* x,         // x-coordinates of hilbert-curve
               unsigned int* y);        // y-coordinates of hilbert-curve

// helper function
point_t* hindex2xy(int hindex, int n);

#endif
