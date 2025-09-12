#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer size>\n", argv[0]);
        return 1;
    }

    long buffer_size = atol(argv[1]);

    if (buffer_size <= 0) {
        fprintf(stderr, "Buffer size must be a positive integer.\n");
        return 1;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    memset(buffer, 0, buffer_size);

    printf("Buffer contents:\n");
    for (long i = 0; i < buffer_size; ++i) {
        printf("%02x ", (unsigned char)buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }

    free(buffer);
    return 0;
}