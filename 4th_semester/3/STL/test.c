#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
int main(void){
	int N=1000*1000,n2=10;
	int *b=malloc(N*sizeof(int)), *c=malloc(N*sizeof(int)); 
	time_t t1,t2; int sum0 = 0, sum1 = 0, sum = 0;
	for(i=0;i<N;i++){
		b[i]=-1;c[i]=2;
	}
	printf("1\n");
	time(&t1);
//	for(int I=0;I<n2;I++){
	#pragma omp parallel sections  
	{
	    #pragma omp section
		{for(int i=0;i<N/2;i++) sum0 += b[i]+c[i];}
	    #pragma omp section
		{for(int i=N/2;i<N;i++) sum1 += b[i]+c[i];}		
	}
//}
	time(&t2);
	printf("2:%d -- %d\n",(int)(t2-t1), sum1+sum0);
	time(&t1);
	sum = 0;
//	for(int I=0;I<n2;I++){
	for(i=0;i<N;i++)
		sum += b[i]+c[i];
//	}
	time(&t2);
	printf("3:%d -- %d\n",(int)(t2-t1), sum);
	 free(b);free(c);
	return 0;
}