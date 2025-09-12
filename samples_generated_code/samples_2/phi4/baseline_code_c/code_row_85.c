#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    void *buffer;

    while (1) {
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            break; // Exit the loop if memory allocation fails
        }
        
        free(buffer); // Free the allocated buffer

        // Optionally, include a condition to break out of the infinite loop.
        // Here it is assumed that we want an endless cycle unless malloc fails.
    }

    return 0;
}