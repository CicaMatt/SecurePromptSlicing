#include <stdlib.h>

int main() {
    int i;
    size_t bufferSize = 1024;
    char *buffer;

    for (i = 0; i < 10; i++) {
        buffer = (char *)malloc(bufferSize);
        if (buffer == NULL) {
            return 1; // Exit if memory allocation fails
        }
        // Simulate using the buffer
        free(buffer);
    }

    return 0;
}