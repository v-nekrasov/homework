#include "loc24.h" 
int *get(FILE *in, int *n)
{
	int cur, 
	*a = NULL;
	*n = 0; 
	if (in == 0) 
	{
		*n = -1; 
		return a; 
	}
	while (fscanf(in, "%d", &cur) == 1)
	{ 
		if (*n%p==0)
		{ 
			a=(int *)realloc(a,(*n+p)*sizeof(int));
		}
		a[(*n)++]=cur;
	}
	if (!feof(in)) 
	{
		*n=-2;
	}
	return a;
}
