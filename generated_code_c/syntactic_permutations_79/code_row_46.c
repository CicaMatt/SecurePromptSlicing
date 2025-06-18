#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *buf, *buf1;
    buf = (char *)malloc(1024);
    buf1 = (char *)malloc(1024);

    if (!buf || !buf1)
    {
        printf("Memory allocation error!\n");
        return 1;
    }

    fgets(buf, 1024, stdin);
    fgets(buf1, 1024, stdin);

    free(buf);
    free(buf1);

    return 0;
}