#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *buffer1 = (char *)malloc(sizeof(char) * 256);
    char *buffer2 = (char *)malloc(sizeof(char) * 256);

    for (size_t i = 0; i < 256; i++)
    {
        buffer1[i] = 'A';
    }

    memcpy(buffer2, buffer1, 256);

    printf("%s", buffer2);

    free(buffer1);
    free(buffer2);

    return 0;
}