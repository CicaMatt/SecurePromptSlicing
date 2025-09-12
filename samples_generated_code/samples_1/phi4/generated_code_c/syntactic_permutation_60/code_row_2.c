#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    if (buffer_size == 0 && argv[1][0] != '0') {
        fprintf(stderr, "Invalid number for buffer size.\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    printf("Buffer content:\n");
    for (size_t i = 0; i < buffer_size; ++i) {
        printf("%02x ", (unsigned char)buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}