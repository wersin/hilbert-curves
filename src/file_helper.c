#include "file_helper.h"

char* str_append(char* s1, char* s2)
{
    char* new_str;
    // allocates memory for both strings + 1 for '\0'
    if((new_str = malloc(strlen(s1)+strlen(s2)+1)) != NULL)
    {
        // ensures the memory is an empty string
        new_str[0] = '\0';
        strcat(new_str, s1);
        strcat(new_str, s2);
    }
    else
    {
        fprintf(stderr,"malloc failed!\n");
        exit(-1);
    }
    return new_str;
}

char* file_ending(char*filename, short html)
{
    char* file_ending = (html) ? ".html" : ".svg";
    return str_append(filename, file_ending);
}

void to_svg(char* filename,
            unsigned int n,
            unsigned int* x_points,
            unsigned int* y_points,
            short html)
{
    int w=600, h=600; // pixel size on screen

    // Begin SVG file
    char deg[2];
    int degree = log10(n) / log10(2);
    sprintf(deg, "%d", degree);
    filename = str_append(filename, deg);
    filename = file_ending(filename, html);
    //filename = str_append("output/", filename),
    FILE *f = fopen(filename, "w");

    // html tags if html was required
    if (html)
    {
        fprintf(f, "<hmtl>\n<body>");
    }
    //canvas size determined by number of iterations
    fprintf(f, "<svg width=\"%dpx\" height=\"%dpx\" viewBox=\"-0.5 0.5 %d "
            "%d\" preserveAspectRatio=\"xMidYMid meet\">",w,h,n,n);
    fprintf(f, "<polyline points=\"");
    unsigned int i = 0;
    for (; i < n * n; ++i)
    {
        fprintf(f, "%d,%d ", x_points[i], y_points[i]);
    }

    //ensures SVG has correct orientation
    fprintf(f,"\" transform=\"scale(1,-1) translate(0,-%d)\"", n);
    fprintf(f, " style=\"fill:none;stroke:black;stroke-width:%lf\" />", 0.1);

    // Complete the HTML file
    fprintf(f, "\n\n</svg>\n");
    if (html)
    {
        fprintf(f, "</hmtl>\n</body>");
    }
    printf("%s was generated\n", filename);
    fclose(f);
}
