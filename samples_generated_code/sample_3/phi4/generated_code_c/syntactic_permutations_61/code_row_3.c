#include <stdio.h>
#include <stdlib.h>

int main() {
    int buffer_size = 1024; // Example buffer size
    char *buffer;

    // Allocate buffer
    buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Free the buffer in a loop
    for (int i = 0; i < 10; ++i) { // Example loop count
        free(buffer);
        buffer = (char *)malloc(buffer_size);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }

    // Final free to avoid memory leak
    free(buffer);

    return 0;
}