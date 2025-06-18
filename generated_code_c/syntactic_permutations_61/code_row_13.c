#include <stdio.h>
#include <stdlib.h>

int main() {
    int *buffer = (int *)malloc(sizeof(int) * buffer_size);
    if (NULL == buffer)
        return 1;

    for (int i = 0; i < buffer_size; i++)
        free(buffer + i);

    free(buffer);
}