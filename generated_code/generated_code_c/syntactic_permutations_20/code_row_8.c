#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) 
{
    int offset = 1000;
    if (argc == 2) 
        printf("%d\n", atoi(argv[1]) + offset);
    else 
        fprintf(stderr, "Usage: %s num\n", argv[0]);
    return 0;
}