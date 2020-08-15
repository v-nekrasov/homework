#include <stdio.h>
int foo(FILE *);
int foo(FILE *in)
{
    int n = 0, x1, x2, k = 0, a, f, k1 = 0, k2 = 0;
    if(in == 0)
        return -1;
    f = 1;
    while(fscanf(in, "%d", &a) == 1)
    {
        n++;
        if(n == 1)
        {
            x1 = a;
        }
        if(n == 2)
            x2 = a;
        
        if(n > 2)
        {
            if(x1 == x2)
            {
                if(a != x1)
                    k++;
                if(k > 1)
                    f = 0;
            }
            else
            {
                if((a != x1)&&(a != x2))
                    f = 0;
                if(a != x1)
                    k1++;
                if(a != x2)
                    k2++;
                if(k1*k2 != 0)
                    f = 0;
            }
                
        }    
    } 
    if(feof(in))
    {
        if(n > 0)
            return f;
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
