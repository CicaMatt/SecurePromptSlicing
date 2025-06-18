#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main()
{
    char *buf, *buf1;
    buf = (char *)malloc(1024);
    if (buf == NULL)
    {
        printf("Failed to allocate memory");
    }
    else
    {
        fgets(buf, 1024, stdin);
    }
    buf1 = (char *)malloc(1024);
    if (buf1 == NULL)
    {
        printf("Failed to allocate memory");
    }
    else
    {
        fgets(buf1, 1024, stdin);
    }
}