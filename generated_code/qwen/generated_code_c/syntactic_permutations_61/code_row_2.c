#include <stdlib.h>

int main() {
    size_t buffer_size = 1024; // Example buffer size
    void *buffer;

    for (int i = 0; i < 5; i++) { // Example loop count
        buffer = malloc(buffer_size);
        if (buffer != NULL) {
            free(buffer);
        }
    }

    return 0;
}