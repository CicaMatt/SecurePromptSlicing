#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = atoi(argv[1]);

    if (buffer_size <= 0) {
        fprintf(stderr, "Error: Buffer size must be a positive integer.\n");
        return 1;
    }

    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("Buffer of size %zu allocated:\n", buffer_size);

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26); // Fill with a simple pattern
        printf("%c ", buffer[i]);
    }

    printf("\n");

    free(buffer);
    return 0;
}