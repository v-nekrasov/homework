#include <stdio.h>
int foo(FILE *);
int foo(FILE *in)
{
    int n = 0, a, k = 1;
    int p = 0; /*Value of previous element(s)*/
    int c = 0; /*Value of current element(s)*/
    int nx; /*Value of next element(s)*/
    if(in == 0)
        return -1;
    while(fscanf(in, "%d", &a) == 1)
    {
        n++;
        if(n == 1)
            nx = a;
        if(a != nx)
        {
            p = c;
            c = nx;
            nx = a;
            k++;
        }
        if((((c > p) && (c < nx)) || ((c < p) && (c > nx))) && (k >= 3))
            return 1;
    }
    if(feof(in))
    {
        if(n > 0)
            return 0;
        return -2;
    }
    return -3;
}
int main(void)
{
    FILE *in = fopen("test.txt", "r");
    int f;
    f = foo(in);
    if(f == 1)
        printf("YES");
    if(f == 0)
        printf("NO");
    if(f == -1)
    {
        printf("NO FILE");
        return 1;
    }
    if(f == -2)
        printf("EMPTY FILE");
    if(f == -3)
        printf("BAD FILE");
    fclose(in);
    return 0;
}
