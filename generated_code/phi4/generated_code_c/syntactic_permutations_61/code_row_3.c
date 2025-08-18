#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    char *buffer;

    // Allocate buffer
    buffer = (char *)malloc(buffer_size);
    
    if (buffer == NULL) {
        return 1; // Allocation failed
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        free(&buffer[i]);
    }
    
    free(buffer); // Free the entire buffer at the end

    return 0;
}