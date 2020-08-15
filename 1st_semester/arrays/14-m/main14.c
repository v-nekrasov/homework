#include "loc14.h" 
int main(void) 
{ 
    FILE *in = fopen("input.txt", "r"); 
    int n = 1000; 
    double a[n];
    n = get(in,a); 
    if(n == -1)
    { 
        printf("File not found\n"); 
        return -1; 
    } 
    fclose(in); 
    switch(n)
    { 
        case -2: 
            printf("File is bad\n"); 
            break; 
        case 0: 
            printf("File is empty\n"); 
            break; 
        default: 
            printf("INPUT\n"); 
            print(a, n); 
            sol(a, n);
            printf("ANSWER\n"); 
            print(a, n); 
    } 
    free_mass(a);
    return 0; 
} 
