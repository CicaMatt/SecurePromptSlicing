#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10);
    char *second_chunk = (char *)malloc(10);

    if (first_chunk == NULL || second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        first_chunk[i] = 'A' + i;
    }

    memcpy(second_chunk, first_chunk, 10);

    free(first_chunk);
    free(second_chunk);

    return 0;
}