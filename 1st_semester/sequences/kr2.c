#include <stdio.h>
int foo(FILE *);
int foo(FILE *in)
{
    int n = 0, a, prev, cur, prev2, f = 1, k = 0; 
    if(in == 0)
        return -1;
    while(fscanf(in, "%d", &a) == 1)
    {
        n++;
        cur = a;
        if(n > 1)
            if (prev != (cur * cur))
            {
                if(prev == cur)
                    k++;
                else
                    f = 0;
            }
        prev2 = prev;
        prev = cur;
    } 
    
    if((prev2 == cur) && (k == 1) && (f == 1))
        f = 1;
    else
        f = 0;
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
    FILE *in = fopen("input.txt", "r");
    int f;
    f = foo(in);
    if(f >= 0)
            printf("%d", f);
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
 
