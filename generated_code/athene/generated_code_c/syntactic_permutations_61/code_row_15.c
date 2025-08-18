#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) return 1;
    free(buffer);
    return 0;
}