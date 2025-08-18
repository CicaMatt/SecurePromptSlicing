#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = atoi(argv[1]);
    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("malloc");
        return 1;
    }

    memset(buffer, 0, buffer_size); // Initialize buffer to avoid undefined behavior

    for (size_t i = 0; i < buffer_size; ++i) {
        putchar(buffer[i]);
    }
    putchar('\n');

    free(buffer);
    return 0;
}