#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include "hilbert.h"
#include "file_helper.h"
#include "arg_parse.h"

/*
 * implementation of the hilbert algorithm in assembler
 */
extern void hilbert(unsigned int degree,     // degree of hilbert curve
                    unsigned int* x,         // x-coordinates of hilbert-curve
                    unsigned int* y);        // y-coordinates of hilbert-curve

int main(int argc, char** argv)
{
    /*
     * this n represents the degree of the hilbert curve it is n = 2^k where k
     * is the degree specified by the execrcise sheet
    */
    int n = 32;
    // use the assembler version of the algorithm or the c implementation
    short use_c = 0;
    // if set creates an html
    short html = 0;
    char* filename = "hilbert_";
    arg_parse(argc, argv, &filename, &n, &use_c, &html);

    // amount of points needed is n^2
    int max_points = n * n;
    unsigned int* x_points = (unsigned int*) malloc(sizeof(unsigned int)*max_points);
    unsigned int* y_points = (unsigned int*) malloc(sizeof(unsigned int)*max_points);

    // default always uses assembler variant
    if (use_c)
    {
        hilbert_c(n, x_points, y_points);
    }
    else
    {
        hilbert(n, x_points, y_points);
    }
    to_svg(filename, n, x_points, y_points, html);
    free(x_points);
    free(y_points);

    return 0;
}
