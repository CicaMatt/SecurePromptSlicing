#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    unsigned char *buffer = malloc(buffer_size);

    if (buffer == NULL) {
        perror("malloc");
        return 1;
    }

    memset(buffer, 0, buffer_size); // Initialize buffer to zero

    for (size_t i = 0; i < buffer_size; ++i) {
        printf("%02X ", buffer[i]);
        if ((i + 1) % 16 == 0) putchar('\n');
    }
    if (buffer_size % 16 != 0) putchar('\n');

    free(buffer);
    return 0;
}