#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = strtoul(argv[1], NULL, 10);
    unsigned char *buffer = malloc(size);

    if (!buffer) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        buffer[i] = i % 256;
    }

    printf("Buffer contents:\n");
    for (size_t i = 0; i < size; ++i) {
        if (i > 0 && i % 16 == 0) {
            printf("\n");
        }
        printf("%02x ", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return EXIT_SUCCESS;
}