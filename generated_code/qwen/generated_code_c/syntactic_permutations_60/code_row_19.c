#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t buffer_size = atoi(argv[1]);
    char *buffer = (char *)malloc(buffer_size);

    if (!buffer) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = '\0'; // Initialize the buffer with null bytes
    }

    printf("Buffer contents: ");
    for (size_t i = 0; i < buffer_size; ++i) {
        if (buffer[i] == '\0') {
            printf("\\0");
        } else {
            putchar(buffer[i]);
        }
    }
    printf("\n");

    free(buffer);
    return EXIT_SUCCESS;
}