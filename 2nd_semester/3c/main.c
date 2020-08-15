#include "matrix.h"
void del_matrix(int**a,int n,int *m)//a -- кривой массив, n -- количество строк, m -- массив длин строк
{
    int i;
    for(i=0;i<n;i++)
        free(a[i]);
    free(a);
	free(m);
}
void pr(FILE*out,int**a,int n,int *m)
{
	int i,j;
    	for(i=0;i<n;i++){
        	for(j=0;j<m[i];j++)
            		fprintf(out,"%d ",a[i][j]);
		fprintf(out,"\n");
    	}
}
int main(void){
    	FILE*in=fopen("1.txt","r");
    	int n,*m;
    	int**matrix;
    	if(in==0){
		printf("File not found\n");
		return -1;
	}
        matrix=matrixget(in,&n,&m);
	fclose(in);
	if(!matrix){
		printf("bad\n");
		return -1;
    	}
	puts("Begin:");
	pr(stdout,matrix,n,m);
	task(matrix,&n,m);
	puts("Result:");
	if(n != 1)
        pr(stdout,matrix,n,m);
    del_matrix(matrix,n,*m);
    return 0;
}

