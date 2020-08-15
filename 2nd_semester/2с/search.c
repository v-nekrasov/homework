#include "header.h"
int mysearch(const char *s, char *maxword)
{
    FILE *in = fopen(s, "r");
    char buf[512];
    char word1[512];
    char word2[512];
    int k = 1, kmax = 1, f = 1;
    if(!in)
        return -1;

    while(fgets(buf, 512, in) != 0)
    {
        int stat = 0, i = 0, j = 0, q = 0;
        while(1)
        {
            if(buf[i] == '"')
            {
                q++;
                if(q%2 == 0)
                {
                    stat = 0;
                    word2[j]=0;
                    j = 0;
                    if(strcmp(word1,word2) == 0)
                    {
                        k++;
                    }
                    else
                    {
                        k = 1;
                    }
                    if(k > kmax)
                        {
                            strcpy(maxword, word1);
                            kmax = k;
                        }
                    if(f)
                    {
                        strcpy(maxword, word2);
                        f = 0;
                    }
                    strcpy(word1, word2);
                }
                if (q%2 == 1)
                    stat = 1;
            }
            else
            {
                if(stat == 1)
                {
                    word2[j] = buf[i];
                    j++;
                }
            }
            if(buf[i] == 0)
            {
                if(q%2 == 1)
                    return -1;
                break;
            }
            i++;
        }
    }

    return 0;
}
