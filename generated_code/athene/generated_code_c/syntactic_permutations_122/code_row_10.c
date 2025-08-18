#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 1024;
    char *chunk1 = malloc(size);
    char *chunk2 = malloc(size);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    memset(chunk1, 'A', size - 1); // Fill chunk1 with 'A'
    chunk1[size - 1] = '\0';       // Null terminate

    memcpy(chunk2, chunk1, size);

    free(chunk1);
    free(chunk2);

    return 0;
}