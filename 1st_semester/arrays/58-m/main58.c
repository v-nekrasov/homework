#include "loc58.h"
int main(void){
    int *a, *b, n, f;
    clock_t t1,t2,t3,t4;
    scanf("%d",&n);
    a = build_massiv(n);
    b = a;
    printf("INPUT ");
    print(a, n);
    t1 = clock();
    mysort(a, n);
    t2 = clock();
    printf("MYSORT ");
    print(a, n);
    printf("TIME OF MYSORT=%lf \n",(double)(t2-t1));

    printf("\n");

    t3 = clock();
    qsort(b, n, sizeof(int), comp);
    t4 = clock();
    printf("QSORT ");
    print(b, n);
    printf("TIME OF QSORT =%lf",(double)(t4-t3));
    printf("\n");
    f = check(a, b, n);
    if(f == 1)
        printf("All RIGHT");
    else
        printf("SOMETHING IS WRONG");
    free(a);
    free(b);
    return 0;
}
