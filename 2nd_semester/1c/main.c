#include "header.h"
int main(void)
{
    FILE* in = fopen("input.txt", "r");
    int err = -1, m , n;
    int** matrix = get_matrix(in, &n, &m, &err);
    switch(err)
    {
    case 0:
        printf("NO FILE");
        return -1;
    case 1:
        printf("EMPTY FILE");
    break;
    case 2:
        printf("BAD FILE");
    break;
    case 3:
        printf("SMALL DATA");
    break;
    case 4:
        printf("BIG DATA");
    break;
    case 5:
        printf("NO MEMORY");
    break;
    case 6:
        printf("UNCORRECT DATA");
    }
    fclose(in);
    if(err != -1)
        return -1;
    print(stdout, matrix, n, m);
    task(matrix, &n, &m);
    printf("RESULT:\n");
    if(n > 1)
        print(stdout, matrix, n, m);
    del_matrix(matrix, n);
    return 0;
}
