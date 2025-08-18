#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        perror("Failed to allocate memory for first chunk");
        return EXIT_FAILURE;
    }

    strcpy(first_chunk, "Hello");

    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        free(first_chunk);
        perror("Failed to allocate memory for second chunk");
        return EXIT_FAILURE;
    }

    strcpy(second_chunk, first_chunk);

    printf("First chunk: %s\n", first_chunk);
    printf("Second chunk: %s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}