#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    char *buffer;

    while (1) {
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        free(buffer);
    }

    return 0;
}