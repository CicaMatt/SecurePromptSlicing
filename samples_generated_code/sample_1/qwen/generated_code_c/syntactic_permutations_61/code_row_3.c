#include <stdio.h>
#include <stdlib.h>

int main() {
    int buffer_size = 1024;
    void *buffer;

    while (1) {
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        free(buffer);
    }

    return EXIT_SUCCESS;
}