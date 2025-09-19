#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    unsigned char *buffer = malloc(buffer_size);

    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = i % 256;
    }

    printf("Buffer contents:\n");
    for (size_t i = 0; i < buffer_size; ++i) {
        if (i > 0 && i % 16 == 0) {
            printf("\n");
        }
        printf("%02x ", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return 0;
}