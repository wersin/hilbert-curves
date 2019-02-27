#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "hilbert.h"
#include "file_helper.h"
#include "arg_parse.h"

extern void hilbert(unsigned int, unsigned int*, unsigned int*);

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
    char* filename = "plotting_data1.svg";

    arg_parse(argc, argv, &filename, &n, &use_c, &html);

    // max amount of points = 2^k * 2^k or n^2
    int max_points = n * n;
    unsigned int* x_points = (unsigned int*) malloc(sizeof(unsigned int)*max_points);
    unsigned int* y_points = (unsigned int*)malloc(sizeof(unsigned int)*max_points);
    // default always uses assembler variant
    clock_t start, end;
    double cpu_time_used;

    if (use_c)
    {
        start = clock();
        //gettimeofday(&tval_before, NULL);
        hilbert_c(n, x_points, y_points);
        //gettimeofday(&tval_after, NULL);
        end = clock();
    }
    else
    {
        start = clock();
        //gettimeofday(&tval_before, NULL);
        hilbert(n, x_points, y_points);
        //gettimeofday(&tval_after, NULL);
        end = clock();
    }
    /*
    long int sec = tval_after.tv_sec - tval_before.tv_sec;
    sec = 0;
    long int usec = (tval_after.tv_usec - tval_before.tv_usec);
    usec = (usec < 0) ? (usec * -1) : usec;
    printf("%ld.%06ld\n", sec, usec);
    */
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%.5f\n", cpu_time_used);
    //to_svg(filename, n, x_points, y_points, html);

    free(x_points);
    free(y_points);

    return 0;
}
