#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    int buffer_size = atoi(argv[1]);
    if (buffer_size <= 0) {
        fprintf(stderr, "Buffer size must be a positive integer.\n");
        return 1;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("Allocated buffer of size %d:\n", buffer_size);
    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26); // Fill with repeating letters A-Z
        putchar(buffer[i]);
    }
    putchar('\n');

    free(buffer);

    return 0;
}