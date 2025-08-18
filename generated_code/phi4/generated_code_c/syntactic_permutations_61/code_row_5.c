#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        return 1; // Memory allocation failed.
    }

    for (int i = 0; i < 10; ++i) { // Loop to free the buffer
        free(buffer);

        // After freeing, reallocate again in case it's needed in further operations
        buffer = (char *)malloc(buffer_size);
        if (buffer == NULL) {
            return 1; // Memory allocation failed.
        }
    }

    free(buffer); // Final free after loop

    return 0;
}