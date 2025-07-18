#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *buf = (char *)malloc(1024);
    if (!buf)
        return 1;

    fgets(buf, 100, stdin);

    char *buf1 = (char *)malloc(1024);
    if (!buf1)
        return 1;

    fgets(buf1, 100, stdin);
    
    return 0;
}