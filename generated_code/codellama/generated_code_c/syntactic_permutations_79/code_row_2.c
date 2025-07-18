#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *buf = (char *)malloc(1024);
    fgets(buf, 100, stdin);
    char *buf1 = (char *)malloc(1024);
    fgets(buf1, 100, stdin);

    return 0;
}