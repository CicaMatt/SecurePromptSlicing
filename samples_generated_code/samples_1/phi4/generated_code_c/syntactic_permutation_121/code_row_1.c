#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 100; // Size of each chunk in bytes
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        perror("Failed to allocate memory for first chunk");
        return EXIT_FAILURE;
    }
    
    const char *data_to_copy = "Hello, world!";
    size_t data_length = strlen(data_to_copy);

    // Ensure the first chunk can hold the data
    if (data_length >= size) {
        fprintf(stderr, "Data is too large for the allocated memory.\n");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    memcpy(first_chunk, data_to_copy, data_length + 1); // Include null terminator

    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        perror("Failed to allocate memory for second chunk");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    memcpy(second_chunk, first_chunk, data_length + 1);

    printf("Second chunk after copying: %s\n", second_chunk);

    free(first_chunk); // Free the first chunk

    printf("Second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk); // Free the second chunk

    return EXIT_SUCCESS;
}