#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t size = strtoul(argv[1], NULL, 10);
    char *buffer = malloc(size);

    if (buffer == NULL) {
        perror("malloc");
        return 1;
    }

    memset(buffer, 0, size); // Initialize buffer to zero

    fwrite(buffer, 1, size, stdout);

    free(buffer);
    return 0;
}