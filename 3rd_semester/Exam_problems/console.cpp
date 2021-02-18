#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	char buf[256];
	printf("argc = %d\n", argc);
    if ( argc != 2 ) 
    {
        printf("error args\n");
        return -1;
    }
    FILE *f = fopen(argv[1], "r");
    while(fscanf(f, "%s", buf)==1)
		printf("{%s} ", buf);
	
	fclose(f);
	return 0;
}