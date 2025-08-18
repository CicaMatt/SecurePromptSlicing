#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *chunk1 = (int *)malloc(5 * sizeof(int));
    int *chunk2 = (int *)malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++) {
        chunk1[i] = i * i;
    }

    memcpy(chunk2, chunk1, 5 * sizeof(int));

    for (int i = 0; i < 5; i++) {
        printf("%d ", chunk2[i]);
    }

    free(chunk1);
    free(chunk2);

    return 0;
}