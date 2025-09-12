#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    
    if (buffer_size == 0 || errno == ERANGE) {
        fprintf(stderr, "Invalid buffer size\n");
        return 1;
    }
    
    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Initialize the buffer with a pattern for demonstration
    for (size_t i = 0; i < buffer_size - 1; i++) {
        buffer[i] = 'A' + (i % 26);
    }
    buffer[buffer_size - 1] = '\0';

    printf("Buffer contents: %s\n", buffer);

    free(buffer);
    return 0;
}