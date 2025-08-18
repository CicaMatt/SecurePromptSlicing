#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    if (buffer_size == 0 && argv[1][0] != '0') {
        fprintf(stderr, "Invalid buffer size\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = '\0'; // Initialize with null characters
    }

    printf("Buffer contents:\n");
    printf("%.*s\n", (int)buffer_size, buffer);

    free(buffer);
    return EXIT_SUCCESS;
}