#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmp(const void *, const void *);
char ** get(FILE *, int *);
void pr(char **, int);

void pr(char **a, int n)
{
	for(int i = 0; i < n; i++)
		puts(a[i]);
}

char ** get(FILE *in, int *n)
{
	char ** str = 0, buf[256], sep[] = "\n \t", *ptr;
	*n = 0;
	while(fgets(buf, 256, in) != 0)
	{
		ptr = buf;
		ptr = strtok(ptr, sep);
		while(ptr != 0)
		{
			str = (char**)realloc(str, (*n + 1) * sizeof(char*));
			str[*n] = (char*)malloc(256);
			strcpy(str[*n], ptr);
			(*n)++;
			ptr = strtok(0, sep);
		}
	}
	return str;
}

int cmp(const void * word1, const void * word2)
{
	return strcmp(*(char**)word1,*(char**)word2);
}

int main(void)
{
	FILE *in = fopen("1.txt", "r"); char **a; int n;
	a = get(in, &n);
	pr(a, n);
	puts("---");
	qsort(a, n, sizeof(char*), cmp);
	pr(a, n);
	for(int i = 0; i < n; i++)
		free(a[i]);
	free(a);
	fclose(in);
	return 0;
}
