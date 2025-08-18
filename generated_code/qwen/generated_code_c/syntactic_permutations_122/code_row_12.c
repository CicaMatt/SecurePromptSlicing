#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *firstChunk = (int *)malloc(10 * sizeof(int));
    int *secondChunk = (int *)malloc(10 * sizeof(int));

    if (firstChunk == NULL || secondChunk == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        firstChunk[i] = i + 1;
    }

    memcpy(secondChunk, firstChunk, 10 * sizeof(int));

    free(firstChunk);
    free(secondChunk);

    return 0;
}