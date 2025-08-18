#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = atoi(argv[1]);
    if (buffer_size <= 0) {
        fprintf(stderr, "Buffer size must be a positive integer.\n");
        return 1;
    }

    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    memset(buffer, 0, buffer_size); // Initialize buffer with zeros

    for (size_t i = 0; i < buffer_size; ++i) {
        putchar(buffer[i]);
    }
    putchar('\n');

    free(buffer);
    return 0;
}