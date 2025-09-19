#include <stdio.h>
#include <stdlib.h>

int main() {
    int buffer_size = 1024;
    void* buffer;

    while (1) {
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            fprintf(stderr, "Failed to allocate memory\n");
            return 1;
        }
        free(buffer);
    }

    return 0;
}