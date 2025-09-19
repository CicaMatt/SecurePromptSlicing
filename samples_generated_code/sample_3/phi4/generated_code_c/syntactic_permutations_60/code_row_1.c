#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t bufferSize = strtoul(argv[1], NULL, 10);
    unsigned char *buffer = malloc(bufferSize);

    if (!buffer) {
        perror("Failed to allocate buffer");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < bufferSize; ++i) {
        buffer[i] = i % 256; // Just an example of filling the buffer
    }

    printf("Buffer contents:\n");
    for (size_t i = 0; i < bufferSize; ++i) {
        if (i > 0 && i % 16 == 0) { 
            printf("\n");
        }
        printf("%02X ", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return EXIT_SUCCESS;
}