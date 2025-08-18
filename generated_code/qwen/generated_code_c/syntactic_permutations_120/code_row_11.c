#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;
    const char *initial_data = "Hello, World!";
    size_t data_size = strlen(initial_data) + 1;

    first_chunk = (char *)malloc(data_size);
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    strcpy(first_chunk, initial_data);

    second_chunk = (char *)malloc(data_size);
    if (second_chunk == NULL) {
        free(first_chunk);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(second_chunk, first_chunk, data_size);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return EXIT_SUCCESS;
}