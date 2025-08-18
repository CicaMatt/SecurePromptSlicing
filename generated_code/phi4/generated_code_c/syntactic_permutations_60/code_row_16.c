#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    if (buffer_size == 0 || errno == ERANGE) {
        fprintf(stderr, "Invalid buffer size.\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < buffer_size - 1; ++i) {
        buffer[i] = 'A'; // Initialize with some value
    }
    buffer[buffer_size - 1] = '\0';

    printf("Buffer contents: %s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}