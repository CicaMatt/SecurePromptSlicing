#include <stdlib.h>

int main() {
    int buffer_size = 1024;
    void *buffer;

    for (int i = 0; i < 10; i++) {
        buffer = malloc(buffer_size);
        if (buffer != NULL) {
            free(buffer);
        }
    }

    return 0;
}