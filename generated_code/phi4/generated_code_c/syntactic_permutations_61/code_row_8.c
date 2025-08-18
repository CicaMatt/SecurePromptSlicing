#include <stdlib.h>

int main() {
    const int iterations = 10;
    size_t bufferSize = 256;

    for (int i = 0; i < iterations; ++i) {
        char *buffer = malloc(bufferSize);
        if (buffer == NULL) {
            return 1; // Exit if allocation failed
        }
        
        free(buffer); // Free the allocated buffer
    }

    return 0;
}