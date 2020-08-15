#include "header.h"
int main(void)
{
    char s[] = "input.txt"; char word[512];
    int v = mysearch(s, word);
    if(v == -1)
    {
        puts("ERROR");
        return -1;
    }
    else
    {
        puts(word);
        return 0;
    }
}
