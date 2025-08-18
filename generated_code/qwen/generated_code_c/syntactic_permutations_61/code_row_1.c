#include <stdlib.h>
#include <stdio.h>

int main() {
    size_t buffer_size = 1024;
    void* buffer;

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        free(buffer);
    }

    return 0;
}