#include <stdlib.h>
#include <stdio.h>

int main() {
    const int buffer_size = 1024;
    
    void *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 10; ++i) {
        free(buffer);

        // Reallocate the buffer
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            return 1;
        }
    }

    free(buffer);
    return 0;
}