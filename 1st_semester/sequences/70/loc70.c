#include "loc70.h"
int foo_loc(FILE *in)
{
    int a, res = 0, k = -1; 
    if(in == 0)
        return -1;
    while(fscanf(in, "%d", &a) == 1)
    {
        switch(a)
        {
            case 0: 
                    if(k == 2)//
                        k++; 
                    else  
                        k = 1;  
                    break; 
            case -1: 
                    if(k == 1)
                    {
                        k++;
                        break;
                    }
                    if(k == 4)
                    {
                        k++;
                        break;
                    }
                    if(k == 3)
                        k = 2;
                    else 
                        k = 0;
                    break; 
            case 2: 
                    if(k == 3)
                        k++;
                    else
                        k = 0;
                    break; 
            default:  k = 0;
        } 
        if(k == 5)
        {
            res++; 
            k = 0; 
        }
    }
    if(feof(in))
    {
        if(k == -1)
            return -2;
        return res;
    }
    return -3;
}
