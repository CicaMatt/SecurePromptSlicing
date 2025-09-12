#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < size - 1; ++i) {
        first_chunk[i] = 'A' + i;
    }
    first_chunk[size - 1] = '\0';

    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        free(first_chunk);
        return EXIT_FAILURE;
    }

    strcpy(second_chunk, first_chunk);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);

    printf("After freeing the first chunk:\n");
    printf("Contents of the second chunk: %s\n", second_chunk);

    free(second_chunk);

    return EXIT_SUCCESS;
}