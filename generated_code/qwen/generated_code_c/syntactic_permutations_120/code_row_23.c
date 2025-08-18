#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(20 * sizeof(char));
    char *second_chunk = (char *)malloc(20 * sizeof(char));

    if (first_chunk == NULL || second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(first_chunk, "Hello, World!");

    strcpy(second_chunk, first_chunk);

    printf("%s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}