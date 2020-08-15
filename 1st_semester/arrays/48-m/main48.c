#include "loc48.h"
int main(void)
{
    FILE *in = fopen("input.txt", "r");
    int n, f;
    int *a;
    a = get_matrix(in,&n);
    if(n == -1)
    {
        printf("FILE IS NOT FOUND\n");
        return -1;
    }
    fclose(in);
    switch(n)
    {
        case -2:
            {
                printf("FILE IS BAD\n");
                break;
            }
        case -3:
            {
                printf("MATRIX IS NOT SQUARE\n");
                break;
            }
        case 0:
            {
                printf("FILE IS EMPTY\n");
                break;
            }
        default:
            {
                printf("INPUT\n");
                print(a, n);
                f = order(a, n, 0, n - 1);
                printf("%d ", f);
            }

    }
    free_matrix(a);
    return 0;
}
