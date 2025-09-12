#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long buffer_size = atoll(argv[1]);

    if (buffer_size <= 0) {
        fprintf(stderr, "Buffer size must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        return EXIT_FAILURE;
    }

    for (long i = 0; i < buffer_size; i++) {
        printf("%02x ", (unsigned char)buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}