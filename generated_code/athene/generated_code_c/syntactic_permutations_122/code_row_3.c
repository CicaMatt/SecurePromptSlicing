#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    memset(chunk1, 'A', 9); // Fill chunk1 with 'A' and leave the last byte for null terminator
    chunk1[9] = '\0';

    memcpy(chunk2, chunk1, 10);

    free(chunk1);
    free(chunk2);

    return 0;
}