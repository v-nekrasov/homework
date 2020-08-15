#include "loc48.h"
int order(int *a, int n, int i, int j)
{
    int prev, f;
    prev = a[i];
    for(int k = 1; k <= j - i/n; k++)
    {
        if(prev > a[i+n*k])
            return 0;
        if(prev == a[i+n*k])
        {
            printf(" i %d", i);
            printf(" k %d", k);
            f = order(a, n, i + (k - 1)*n + 1, j);
            printf(" f %d", f);

            printf("\n");
            if(f == 0)
                return 0;
        }
        prev = a[i+n*k];
    }
    return 1;
}
