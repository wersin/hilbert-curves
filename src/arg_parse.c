#include "arg_parse.h"

void print_usage(char* program_name)
{
    printf("%s [-h] [-t] [-d n] [-f <name>] [-c] -- prints the Nth grade of the ", program_name);
    printf("hilbert curve to an svg/html file\n\n");
    printf("where:\n");
    printf("\t-h  show this help text\n");
    printf("\t-f  outputs the svg to specified file name\n");
    printf("\t-d  degree of the hilbert curve (default 1)\n");
    printf("\t-c  if set uses c implementation (default uses assembler)\n");
    printf("\t-t  if set creates an html file of the svg\n");
}

void arg_parse(int argc, char** argv, char** filename, int* n, short* c, short* html)
{
    int opt;
    while ((opt = getopt(argc, argv, "d:f:cth")) != -1) {
        switch (opt) {
            case 'd':
                *n = atoi(optarg);
                *n = (*n < 0) ? 1 : *n;
                // convert n to appropiate value for iterative algorithm
                *n = 1 << (*n); // == 2^(n)
                // dont allow 0 as input
                *n = (*n == 1) ? 2 : *n;
                break;
            case 'f':
                *filename = optarg;
                *filename = str_append(*filename, "_");
                break;
            case 'c':
                //use_c = atoi(optarg);
                *c = 1;
                break;
            case 't':
                *html = 1;
                break;
            case 'h':
                print_usage(argv[0]);
                exit(-1);
                break;
            default:
                printf("Invalid option\n");
        }
    }
}
