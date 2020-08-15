#include "loc48.h"
void print(int *a, int n)
{
    for(int i = 0; i < n*n; i++)
    {
        printf("%d ", a[i]);
        if (i % n == n - 1)
            printf("\n");
    }
}
