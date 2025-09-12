#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void store_in_buffer(char *buf, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        buf[i] = 'A' + (i % 26); // Example: fill with letters A-Z
    }
}

int main() {
    char *buf = malloc(BUFFER_SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    store_in_buffer(buf, BUFFER_SIZE);

    printf("Buffer content:\n%s\n", buf);

    free(buf);
    return 0;
}