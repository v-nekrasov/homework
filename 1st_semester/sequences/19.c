#include <stdio.h>
double D (FILE *);
double D (FILE *in)
{
    double a, n = 0, sum = 0, sum2 = 0;
    if(in == 0)
        return -1.0;
    while(fscanf(in, "%lf", &a) == 1)
    {
        n = n + 1;
        sum = sum + a;
        sum2 = sum2 + a*a;
    }
    if(feof(in))
    {
        if(n > 0)
        {
            double M = sum/n;
            return (sum2 - 2*M*sum + n*M*M)/n;
        }
        return -2.0;
    }
    return -3.0;
}
int main(void)
{
    double d;
    FILE *in = fopen("test.txt", "r");
    d = D(in);
    if(d >= 0)
        printf("result = %lf", d);
    else
    {
        if((int)d == -1)
        {
            printf("No file");
            return 0;
        }
        if((int)d == -2)
            printf("File is empty");
        if((int)d == -3)
            printf("Bad file");
    }
    fclose(in);
    return 0;
}
