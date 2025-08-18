#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    char *first_chunk = (char *)malloc(length * sizeof(char));
    if (!first_chunk) {
        perror("Failed to allocate first chunk");
        return EXIT_FAILURE;
    }

    strcpy(first_chunk, "HelloWorld");

    char *second_chunk = (char *)malloc((length + 1) * sizeof(char)); // +1 for null terminator
    if (!second_chunk) {
        free(first_chunk);
        perror("Failed to allocate second chunk");
        return EXIT_FAILURE;
    }

    memcpy(second_chunk, first_chunk, length * sizeof(char));
    second_chunk[length] = '\0'; // Ensure the string is null-terminated

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk); // Free the first chunk

    printf("Contents of the second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk); // Free the second chunk
    
    return EXIT_SUCCESS;
}