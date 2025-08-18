#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    if (buffer_size == 0 || errno == ERANGE) {
        fprintf(stderr, "Invalid buffer size.\n");
        return 1;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26); // Fill with A-Z pattern
    }

    printf("Buffer contents:\n");
    for (size_t i = 0; i < buffer_size; ++i) {
        putchar(buffer[i]);
        if ((i + 1) % 80 == 0) { // Newline every 80 characters for readability
            putchar('\n');
        }
    }
    printf("\n");

    free(buffer);
    return 0;
}