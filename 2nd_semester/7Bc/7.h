#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct my{
    int group;
    char name[22];
    int err;
}My;
My * init(int n, const char *s, int a);
void print(FILE *out, My *student);
int my_pow(int a, int n);
My* get_student(char *buf);
My ** readdata(FILE *in, int *n);
void my_free(My ** a, int n);
int cmp(const void *x, const void *y);
int is_equal(const My *one, const My *two);
My ** task(My ** student_1,My ** student_2, int n1, int n2, int *n);
