#include <stdio.h>
#include <stdlib.h>
int main()
{
    unsigned long int buffer_size = 1024;
    char *buffer = (char *)malloc(sizeof(char) * buffer_size);
    if (!buffer)
        return -1;
    free(buffer);
    return 0;
}