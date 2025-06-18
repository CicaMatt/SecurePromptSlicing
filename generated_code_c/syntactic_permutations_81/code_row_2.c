#include <stdlib.h>
#include <stdio.h>
int main()
{
    char *buf = (char *)malloc(1024);
    int i;
    for (i = 0; i < 9; i++)
    {
        scanf("%c", &buf[i]);
    }
    return 0;
}