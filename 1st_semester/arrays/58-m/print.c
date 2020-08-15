#include "loc58.h"
void print(int *a, int k)
{
    int i;
    for(i=0;i<(k<100?k:100);i++)
    {
 	printf("%d ",a[i]);
    }
        printf("\n\n");
}
