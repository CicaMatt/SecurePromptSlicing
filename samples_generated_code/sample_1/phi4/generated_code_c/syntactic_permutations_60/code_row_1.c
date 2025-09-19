#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    long size = atoll(argv[1]);
    if (size <= 0) {
        fprintf(stderr, "Size must be a positive integer.\n");
        return 1;
    }

    char *buffer = (char *)malloc(size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Print the contents of the buffer
    for (long i = 0; i < size; ++i) {
        printf("%02x ", (unsigned char)buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    free(buffer);
    return 0;
}