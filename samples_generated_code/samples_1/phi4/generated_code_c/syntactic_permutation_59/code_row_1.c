#include <stdio.h>
#include <stdlib.h>

void fillBufferWithA(size_t buffer_size) {
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }

    // Example usage: Print the contents of the buffer
    printf("Buffer contents:\n%s\n", buffer);

    free(buffer); // Free allocated memory to prevent memory leaks
}

int main() {
    size_t buffer_size;
    
    printf("Enter buffer size: ");
    if (scanf("%zu", &buffer_size) != 1 || buffer_size == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    fillBufferWithA(buffer_size);

    return EXIT_SUCCESS;
}