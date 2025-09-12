#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024; // Example buffer size
    char *buffer;

    for (int i = 0; i < 10; ++i) { // Loop to allocate and free the buffer
        buffer = (char *)malloc(buffer_size);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }

        // Freeing the allocated memory
        free(buffer);

        printf("Iteration %d: Allocated and freed a buffer of size %zu bytes.\n", i + 1, buffer_size);
    }

    return 0;
}