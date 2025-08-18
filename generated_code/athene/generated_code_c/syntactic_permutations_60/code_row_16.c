#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer size>\n", argv[0]);
        return 1;
    }

    long bufferSize = atol(argv[1]);
    if (bufferSize <= 0) {
        fprintf(stderr, "Buffer size must be positive.\n");
        return 1;
    }

    char *buffer = malloc(bufferSize);
    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        return 1;
    }

    memset(buffer, 'A', bufferSize - 1); // Fill with 'A' except the last byte
    buffer[bufferSize - 1] = '\0';       // Null terminate

    printf("%s\n", buffer);

    free(buffer);
    return 0;
}