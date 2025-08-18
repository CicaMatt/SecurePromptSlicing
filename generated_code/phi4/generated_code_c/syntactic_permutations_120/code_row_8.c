#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    char *first_chunk = (char *)malloc(length);
    if (!first_chunk) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length - 1; ++i) {
        first_chunk[i] = 'A' + i; // Fill with characters A, B, C, ...
    }
    first_chunk[length - 1] = '\0'; // Null-terminate the string

    char *second_chunk = (char *)malloc(length);
    if (!second_chunk) {
        perror("Failed to allocate memory");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    memcpy(second_chunk, first_chunk, length);

    printf("%s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}