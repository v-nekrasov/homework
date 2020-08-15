#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *lineget(FILE *in);
int intget(char *str, int *k);
void del_matrix(int**a,int n,int *m);
int**matrixget(FILE*in,int*n,int**m);
void pr(FILE*out,int**a,int n,int *m);
void task(int **a, int *n, int *m);
