#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *buf = (char *)malloc(1024);
    fread(buf, 10, 10, stdin);
}