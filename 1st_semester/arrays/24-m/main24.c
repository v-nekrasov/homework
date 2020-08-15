#include "loc24.h" 
int main(void) 
{ 
    FILE *in = fopen("input.txt", "r"); 
    int n; 
    int *a;
    int i = 0;
    a = get(in,&n); 
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
            i = sol(a, n);
            printf("POSITION: %d ", i); 
    } 
    free_mass(a);
    return 0; 
} 
