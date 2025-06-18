#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *buf, *buf1;

    buf = (char *)malloc(1024);
    if (buf == NULL)
        return 1;
    
    buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        return 1;
    }

    fgets(buf, 100, stdin);
    fgets(buf1, 100, stdin);

    free(buf);
    free(buf1);

    return 0;
}