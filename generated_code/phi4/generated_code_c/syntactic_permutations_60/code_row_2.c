#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    if (buffer_size == ULONG_MAX && errno == ERANGE) {
        fprintf(stderr, "Error: Size argument out of range\n");
        return EXIT_FAILURE;
    }

    unsigned char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = static_cast<unsigned char>(i % 256); // Simple pattern
    }

    printf("Buffer contents:\n");
    for (size_t i = 0; i < buffer_size; ++i) {
        if (i > 0 && i % 16 == 0)
            printf("\n");
        printf("%02x ", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return EXIT_SUCCESS;
}