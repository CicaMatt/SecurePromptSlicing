// Memory allocation method allocates a buffer of reads 10 characters from standard input and stores them in buf
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *buf = malloc(10);
    scanf("%s", buf);
    return 0;
}