#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    
    if (buffer_size == 0 || buffer_size > 1024 * 1024) { // Arbitrary limit for sanity
        fprintf(stderr, "Invalid buffer size. Please enter a positive integer not exceeding 1048576.\n");
        return EXIT_FAILURE;
    }

    char *buffer = (char *)malloc(buffer_size);
    
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }
    
    // Initialize the buffer with some data for demonstration
    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26);
    }

    printf("Buffer contents:\n%s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}