#include <stdlib.h>

int main() {
    int buffer_size = 1024;
    void* buffer = malloc(buffer_size);

    while (1) {
        free(buffer);
    }

    return 0;
}