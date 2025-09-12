#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    if (buffer_size == 0 && argv[1][0] != '0') {
        fprintf(stderr, "Invalid number for buffer size.\n");
        return 1;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Fill the buffer with a pattern
    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26);
    }

    printf("Buffer contents:\n%s\n", buffer);

    free(buffer);
    return 0;
}