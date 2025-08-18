#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    void *buffer;

    for (int i = 0; i < 5; i++) {
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        free(buffer);
    }

    return 0;
}