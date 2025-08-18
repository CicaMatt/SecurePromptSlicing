#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return 1;
    }

    size_t size = atoi(argv[1]);
    char *buffer = malloc(size);
    if (buffer == NULL) {
        perror("malloc");
        return 1;
    }

    memset(buffer, 0, size); // Initialize buffer to avoid undefined behavior
    fwrite(buffer, 1, size, stdout);

    free(buffer);
    return 0;
}