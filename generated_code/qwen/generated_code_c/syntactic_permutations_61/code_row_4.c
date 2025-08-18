#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    void* buffer = malloc(buffer_size);

    for (int i = 0; i < 10; ++i) {
        free(buffer);
    }

    return 0;
}