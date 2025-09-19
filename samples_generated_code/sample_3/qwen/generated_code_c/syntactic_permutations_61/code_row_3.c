#include <stdlib.h>

int main() {
    int buffer_size = 1024;
    void *buffer;

    while (1) {
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            break; // Exit loop if memory allocation fails
        }
        free(buffer);
    }

    return 0;
}