#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    if (buffer_size == 0 || buffer_size > SIZE_MAX) {
        fprintf(stderr, "Invalid buffer size\n");
        return 1;
    }

    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("Buffer contents:\n");
    for (size_t i = 0; i < buffer_size; ++i) {
        putchar(i % 128); // Print values from 0 to 127 repeatedly
    }
    putchar('\n');

    free(buffer);
    return 0;
}