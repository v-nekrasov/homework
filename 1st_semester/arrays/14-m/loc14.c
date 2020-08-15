#include "loc14.h"
void sol(double a[], int n)
{
    double x = 1000, l = 0, r = 0;
    int i, j = 0;
    for(i = 0; i < n; i++)
    {
        if(((a[i] - x) < 0.000001)&&((a[i] - x) > -0.000001))
        {
            j = i + 1;
            while(((a[j] - x) < 0.000001)&&((a[j] - x) > -0.000001)&&(j < n))
               {
                   j++;
               }
            if(j < n)
                r = a[j];
            else
                r = 0;
            if(i == 0)
                l = 0;
            else
            l = a[i - 1]; 
            for(int k = i; k < j; k++)
                a[k] = (l+r)/2;
            i = j;
        }
        
    }
}


