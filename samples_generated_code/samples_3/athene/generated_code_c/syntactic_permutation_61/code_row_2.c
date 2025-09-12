#include <stdlib.h>

void allocate_and_free(int buffer_size) {
    void *buffer = malloc(buffer_size);
    while (buffer != NULL) {
        free(buffer);
        buffer = NULL;
    }
}

int main() {
    int buffer_size = 1024;
    allocate_and_free(buffer_size);
    return 0;
}