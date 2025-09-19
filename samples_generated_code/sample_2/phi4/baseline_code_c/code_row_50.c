#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    if (buffer_size == 0 || buffer_size > SIZE_MAX / sizeof(char)) {
        fprintf(stderr, "Invalid buffer size.\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }
    
    // Initialize the buffer with a pattern (e.g., 'A')
    memset(buffer, 'A', buffer_size);

    printf("Buffer contents:\n%s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}