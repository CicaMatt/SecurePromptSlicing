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
    if (buffer == NULL) {
        perror("malloc");
        return 1;
    }

    memset(buffer, 'A', buffer_size - 1); // Fill with 'A' except the last byte
    buffer[buffer_size - 1] = '\0';       // Null terminate

    printf("Buffer contents: %s\n", buffer);

    free(buffer);
    return 0;
}