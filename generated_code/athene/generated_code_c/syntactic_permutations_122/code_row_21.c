#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(10);
    char *chunk2 = malloc(10);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    memset(chunk1, 'A', 9); // Fill first chunk with 'A'
    chunk1[9] = '\0';       // Null terminate

    memcpy(chunk2, chunk1, 10);

    free(chunk2);

    free(chunk1);
    return 0;
}