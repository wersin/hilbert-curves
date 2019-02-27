#ifndef ARG_PARSE_H_
#define ARG_PARSE_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "file_helper.h"

/*
 * parses arguments passed by command line
*/
void arg_parse(int argc,                // stores # of arguments
               char** argv,             // store value of arguments
               char** filename,         // name of output file
               int* n,                  // degree of hilbert curve
               short* c,                // c-flag, if set uses c algorithm
               short* html);            // html-flag, if set outputs an html doc

/*
 * prints a usage message
*/
void print_usage(char* program_name);

#endif
