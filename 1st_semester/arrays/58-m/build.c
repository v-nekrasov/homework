#include "loc58.h" 
int * build_massiv(int n)
{   
    int *a;
    srand(time(NULL));
    a=(int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
        a[i]=rand()%100;
    return a;
}
