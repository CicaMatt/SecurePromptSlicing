#include <stdio.h>
#include <stdlib.h>

int main()
{
    void *chunk1 = malloc(10);
    void *chunk2 = malloc(10);

    if (chunk1 == NULL || chunk2 == NULL)
        exit(1);

    memcpy(chunk2, chunk1, 10);

    free(chunk1);
    free(chunk2);

    return 0;
}