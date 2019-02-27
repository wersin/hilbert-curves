#ifndef FILE_HELPER_H_
#define FILE_HELPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
 * creates an svg/html file from the set of points
 */
void to_svg(char* filename,     // name of output file
        unsigned int degree,    // degree of hilbert curve
        unsigned int* x,        // x-coordinates of hilbert curve
        unsigned int* y,        // y-coordinates of hilbert curve
        short html);            // html flag, if set outputs an html file

/*
 * appends s1 to s2 and returns the newly created string
 */
char* str_append(char* s1, char* s2);

/*
 * changes the file ending to .svg or .html
 * depending if html is set or not
 */
char* file_ending(char*filename, short html);

#endif
