#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return 1;
    }

    size_t size = atoi(argv[1]);

    if (size <= 0) {
        fprintf(stderr, "Size must be a positive integer\n");
        return 1;
    }

    char *buffer = malloc(size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    for (size_t i = 0; i < size; ++i) {
        buffer[i] = 'A' + (rand() % 26); // Filling with random uppercase letters
    }

    printf("Buffer contents: %.*s\n", (int)size, buffer);

    free(buffer);
    return 0;
}