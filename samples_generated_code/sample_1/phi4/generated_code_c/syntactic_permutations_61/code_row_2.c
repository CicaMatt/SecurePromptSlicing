#include <stdlib.h>

int main() {
    size_t buffer_size = 1024; // Example buffer size, can be adjusted

    while (1) { // Infinite loop to repeatedly allocate and free memory
        void *buffer = malloc(buffer_size); // Allocate the buffer
        if (!buffer) break; // Break if allocation fails
        
        free(buffer); // Free the allocated buffer
    }

    return 0;
}