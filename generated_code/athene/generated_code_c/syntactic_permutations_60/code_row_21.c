#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        exit(1);
    }

    size_t buffer_size = atoi(argv[1]);
    char *buffer = malloc(buffer_size);

    if (buffer == NULL) {
        perror("malloc");
        exit(1);
    }

    memset(buffer, 0, buffer_size); // Initialize buffer to zero

    printf("Buffer of size %zu allocated.\n", buffer_size);
    for (size_t i = 0; i < buffer_size; ++i) {
        printf("%02X ", (unsigned char)buffer[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    if (buffer_size % 16 != 0) printf("\n");

    free(buffer);
    return 0;
}