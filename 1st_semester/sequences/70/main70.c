#include "loc70.h"
int main(void)
{
    FILE *in = fopen("input.txt", "r");
    int n;
    n = foo_loc(in);
    switch(n) 
    { 
        case -1: 
            printf("NO FILE");
            return 1;
        case -2: 
            printf("EMPTY FILE"); 
            break; 
        case -3: 
            printf("BAD FILE"); 
            break; 
        default: 
            printf("KOL_FRAG=%d\n",n); 
    }
    fclose(in);
    return 0;
}
 
