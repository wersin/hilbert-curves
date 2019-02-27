#include "hilbert.h"

void hilbert_c(unsigned int degree, unsigned int* x, unsigned int* y)
{
    point_t* p1 = (point_t*) malloc(sizeof(point_t));
    unsigned int i = 0;
    for (; i < degree * degree; i += 1) {
        p1 = hindex2xy(i, degree);
        x[i] = p1->x;
        y[i] = p1->y;
    }
}

point_t* hindex2xy(int hindex, int n)
{
    // positions for first iteration
    point_t* p1 = (point_t*) malloc(sizeof(point_t));
    int positions[4][2] =
    {
        {0, 0},
        {0, 1},
        {1, 1},
        {1, 0},
    };

    int* tmp = positions[hindex & 0x3];
    hindex = hindex >> 2;
    int x = tmp[0];
    int y = tmp[1];

    for (int i = 4; i <= n; i *= 2)
    {
        int n2 = i / 2;
        switch(hindex & 0x3)
        {
            case 0: {
                int temp = x;
                x = y;
                y = temp;
                break;
                    }
            case 1:{ /* left-upper */
                x = x;
                y = y + n2;
                break;
                   }
            case 2: { /* right-upper */
                x = x + n2;
                y = y + n2;
                break;
                    }
            case 3: { /* right-bottom */
                int temp = y;
                y = (n2-1) - x;
                x = (n2-1) - temp;
                x = x + n2;
                break;
                    }
        } // end of switch
        hindex = hindex >> 2;
    } // end of for
    p1->x = x;
    p1->y = y;
    // Debug output
    // printf("(%d, %d)\n", x, y);
    return p1;
}
