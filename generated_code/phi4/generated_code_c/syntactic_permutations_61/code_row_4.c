#include <stdlib.h>

int main() {
    size_t buffer_size = 1024; // Example buffer size, change as needed

    void *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return 1; // Allocation failed
    }

    for (size_t i = 0; i < 10; ++i) { // Free the buffer in a loop 10 times
        free(buffer);

        // Reallocate memory to avoid using freed pointer
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            return 1; // Allocation failed, exit
        }
    }

    free(buffer); // Final free after loop

    return 0;
}