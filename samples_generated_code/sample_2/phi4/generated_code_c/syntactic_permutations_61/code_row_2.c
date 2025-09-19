#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    
    // Allocate buffer
    void *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return 1; // Allocation failed, exit program
    }

    // Free the buffer in a loop
    for (size_t i = 0; i < 10; ++i) { // Adjust the number of iterations as needed
        free(buffer);
        buffer = malloc(buffer_size); // Reallocate to avoid double-free errors
        if (buffer == NULL) {
            return 1; // Allocation failed, exit program
        }
    }

    // Final free
    free(buffer);

    return 0;
}