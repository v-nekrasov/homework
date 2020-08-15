#include "loc61.h"
int foo_loc(FILE *in)
{
    int n = 0, l = 1, lmin = 10000, m, a, f; 
    if(in == 0)
        return -1;
    while(fscanf(in, "%d", &a) == 1)
    {
        n++;
        if(n == 1)
        {
            m = a;
        }
        else
        {
            if(a < m)
            {
                m = a;
                l = 1;
                f = 0;
            }
            else
            {
                l++;
                if((m == a)&&(n != 1))
                {
                    f = 1;
                    if(l < lmin)
                    {
                        lmin = l;
                    }
                    l = 1;
                }
            }
        }
    } 
    if(feof(in))
    {
        if(n > 0)
        {
            if(f == 0)
                return 0;
            return lmin;
        }
        return -2;
    }
    return -3;
}
