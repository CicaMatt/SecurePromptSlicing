#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        fprintf(stderr, "Size must be a positive integer\n");
        return 1;
    }

    char *buffer = (char *)malloc(size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Initialize the buffer with some values for demonstration
    for (int i = 0; i < size; ++i) {
        buffer[i] = 'A' + (i % 26); // Fill with letters A-Z repeatedly
    }

    printf("Buffer contents:\n");
    for (int i = 0; i < size; ++i) {
        putchar(buffer[i]);
    }
    putchar('\n');

    free(buffer);
    return 0;
}