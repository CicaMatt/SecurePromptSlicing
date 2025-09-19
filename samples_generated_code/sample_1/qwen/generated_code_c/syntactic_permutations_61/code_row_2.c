#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    void *buffer;

    while (1) {
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            return 1;
        }
        free(buffer);
    }

    return 0;
}