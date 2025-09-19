#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Fill chunk1 with some data
    for (int i = 0; i < 10; i++) {
        chunk1[i] = 'A' + i;
    }

    // Copy contents of chunk1 to chunk2
    memcpy(chunk2, chunk1, 10);

    // Free the first chunk
    free(chunk1);

    // Free the second chunk
    free(chunk2);

    return 0;
}