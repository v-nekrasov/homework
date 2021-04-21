#include <stdlib.h>
#include <stdio.h>
float Deg2N(double x, long long int n);
float Deg2N(double x, long long int n)
{  
	long long int *p = (long long int *) (&x);
	n <<= 52;
	(*p) += n;
	return x;
}
int main(void)
{
	
	float x = 2.;
	printf("Deg2N = %f", Deg2N(x, 3));
	return 0; 
}