#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    void *buffer = malloc(buffer_size);

    while (1) {
        free(buffer);
        buffer = NULL; // Optional: set buffer to NULL after freeing
    }

    return 0;
}