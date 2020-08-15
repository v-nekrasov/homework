#include "header.h"
int** get_matrix(FILE* in, int* n, int* m, int* err)
{
    int** matrix = 0;
    int i, j, x, k = 0, f;
    if(in==0)
        *err=0;
    else
    {
        f = fscanf(in, "%d%d", n, m);
        if(f > 1)
        {
            if(((*n)<= 0) || ((*m) <= 0))
                *err = 6;
            else
            {
                matrix = (int**)malloc(*n * sizeof(int*));
            for(i = 0; i < *n; i++)
                matrix[i] = (int*)malloc(*m * sizeof(int));
            if(matrix == NULL)
                *err = 5;
            for(i = 0; i < *n; i++)
                for(j = 0; j < *m; j++)
                    matrix[i][j] = 0;
            i = 0;
            j = 0;
            while(fscanf(in, "%d", &x)== 1)
            {
                if(i<*n)
                {
                    k++;
                    *(matrix[i] + j) = x;
                    j++;
                    if(j%(*m) == 0)
                    {
                        j = 0;
                        i++;
                    }
                }
                else
                    k++;
            }
            if(feof(in))
            {
                *err = -1;
                if(k < (*m)*(*n))
                    *err = 3;
                if(k > (*m)*(*n))
                    *err = 4;
            }
            else
                *err = 2;
            }
        }
        else
        {
            if(f == 0)
                *err = 2;
            if(f == -1)
                *err = 1;
            if(f == 1)
                *err = 3;
        }

    }
    return matrix;

}

void print(FILE* out, int** matrix, int n, int m)
{
    fprintf(out, "\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            fprintf(out, "%d ", matrix[i][j]);
        fprintf(out, "\n");
    }
}
void del_matrix(int** matrix, int n)
{
    for(int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}
void task(int** matrix, int* n, int* m)
{
    int pos = 0, neg = 0, f = 0;
    for(int i = 0; i < *n; i++)
    {
        f = 0;
        for(int k = 0; k < *n; k++)
            if(k!=i)
            {
                for(int j = 0; j < *m; j++)
                {
                    if(matrix[i][j]- matrix[k][j] > 0)
                        pos++;
                    if(matrix[i][j]- matrix[k][j] < 0)
                        neg++;
                }
                if((pos>0)&&(neg>0))
                {
                    f++;
                    pos = 0;
                    neg = 0;
                    if(f == *n-1)
                    {
                        for(int p = i; p < *n - 1; p++)
                        {
                            matrix[p] = matrix[p+1];
                        }
                        i = i - 1;
                        *n = *n - 1;
                    }
                }
                else
                {
                    pos = 0;
                    neg = 0;
                    break;
                }

            }
    }
}
