#include "loc48.h"
int check_q(int n)
{
    int i = 1;
    while (i*i <= n)
    {
        if(i*i == n)
            return 1;
        i++;
    }
    return 0;
}
