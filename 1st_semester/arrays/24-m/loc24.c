#include "loc24.h"
int sol(int *a, int n)
{
    int x = 13;
    int l = 0;
    int r = n - 1;
    int i;
    if(a[l] > x)
        return 0;
    while (r - l > 1)
    {
        if(x == a[(r+l)/2])
        {
            return i = (r+l)/2 + 1;
        }
        if(x < a[(r+l)/2])
            r = (r+l)/2;
        else
            l = (r+l)/2;
        
        
    }
    i = r;
    return i;
}


