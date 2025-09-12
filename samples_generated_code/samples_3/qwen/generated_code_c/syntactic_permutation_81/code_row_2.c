#include <stdio.h>
#include <stdlib.h>

void allocateBuffer(char **buf) {
    *buf = (char *)malloc(1024);
    if (*buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

int main() {
    char *buffer;
    allocateBuffer(&buffer);

    // Example usage: Fill buffer with some data
    for (int i = 0; i < 1024; i++) {
        buffer[i] = 'A';
    }

    // Free the allocated memory
    free(buffer);
    return 0;
}