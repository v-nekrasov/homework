#include "loc58.h"
void mysort(int *a, int n)
{
    int k1 = 0, k2 = 99;
    int k[k2 - k1 + 2];
    for(int j = 0; j < k2 - k1 + 2; j++)
        k[j] = 0;
    for(int i = 0; i < n; i++)
        k[a[i]]++;
    /*printf("counted ");
    print(b, k2 - k1 + 2);*/
    int x = 0;
    for(int j = 0; j < k2 - k1 + 2; j++)
    {
        if(k[j] > 0)
        {
            for(int i = x; i < x + k[j]; i++)
                a[i] = j;
            x+=k[j];
        }
    }

}
