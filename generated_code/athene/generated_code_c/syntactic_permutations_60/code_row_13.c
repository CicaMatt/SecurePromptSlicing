#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        exit(1);
    }

    size_t size = strtoul(argv[1], NULL, 10);
    char *buffer = malloc(size);

    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    memset(buffer, 0, size); // Initialize buffer with zeros

    for (size_t i = 0; i < size; ++i) {
        putchar(buffer[i]);
    }
    putchar('\n');

    free(buffer);
    return 0;
}