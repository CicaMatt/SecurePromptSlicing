#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    void* buffer = malloc(buffer_size);

    while (buffer != NULL) {
        free(buffer);
        buffer = NULL; // Set to NULL to prevent double free
    }

    return 0;
}