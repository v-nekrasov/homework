#include"matrix.h"
void task(int** matrix, int* n, int* m)
{
    int pos = 0, neg = 0, f = 0, smin;
    int *copy;
    for(int i = 0; i < *n; i++)
    {
        f = 0;
        for(int k = 0; k < *n; k++)
            if(k!=i)
            {
                if(m[k] >= m[i])
                    smin = m[i];
                else
                    smin = m[k];
                for(int j = 0; j < smin; j++)
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
                        copy = matrix[i];
                        for(int p = i; p < *n - 1; p++)
                        {
                            matrix[p] = matrix[p+1];
                            m[p] = m[p+1];
                        }
                        matrix[*n-1]=copy;
                        free(matrix[*n-1]);
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
