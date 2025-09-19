#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *chunk1, *chunk2;
    size_t size = 10;

    chunk1 = (int *)malloc(size * sizeof(int));
    if (chunk1 == NULL) return 1;

    for (size_t i = 0; i < size; ++i) {
        chunk1[i] = i;
    }

    chunk2 = (int *)malloc(size * sizeof(int));
    if (chunk2 == NULL) {
        free(chunk1);
        return 1;
    }

    memcpy(chunk2, chunk1, size * sizeof(int));

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", chunk2[i]);
    }
    printf("\n");

    free(chunk1);
    free(chunk2);

    return 0;
}