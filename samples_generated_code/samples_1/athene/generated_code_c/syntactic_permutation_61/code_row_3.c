#include <stdlib.h>

void allocate_and_free(int buffer_size) {
    char *buffer = malloc(buffer_size);
    while (buffer != NULL) {
        free(buffer);
        buffer = NULL;
    }
}