#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(1024);
    char *chunk2 = malloc(1024);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    memset(chunk1, 'A', 1023); // Fill with some data
    chunk1[1023] = '\0';

    memcpy(chunk2, chunk1, 1024);

    free(chunk1);
    free(chunk2);

    return 0;
}