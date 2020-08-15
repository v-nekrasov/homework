#include "loc48.h"
int *get_matrix(FILE *in, int *n)
{
    int cur, *a = NULL;
    *n = 0;
    if (in == 0)
    {
        *n = -1;
        return a;
    }
    while (fscanf(in, "%d", &cur) == 1)
    {
        if (*n % p == 0)
        {
            a=(int *)realloc(a,(*n+p)*sizeof(int));
         }
         a[(*n)++]=cur;
     }
    if (!feof(in))
    {
        *n=-2;
    }
    if(*n>0)
    {
        if(check_q(*n) == 0)
            *n=-3;
        else
        {
            double x;
            x = sqrt((double)(*n));
            *n=(int)x;
        }
    }
    return a;
}
