#include <stdlib.h>

void free_in_loop(int buffer_size) {
    int* buffer = malloc(buffer_size * sizeof(int));
    for (int i = 0; i < buffer_size; ++i) {
        free(buffer + i);
    }
}