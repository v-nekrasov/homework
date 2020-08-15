#include "loc14.h" 
int get(FILE *in, double a[])
{ 
    int n = 0; 
    if(in == 0) 
        return -1;
    while(fscanf(in, "%lf", a+n) == 1) 
        n++; 
    if(!feof(in)) 
		return -2;
	return n;
}
