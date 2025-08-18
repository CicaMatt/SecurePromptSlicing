#include <stdlib.h>

int main() {
    int buffer_size = 1024;
    char *buffer = malloc(buffer_size);
    
    while (buffer != NULL) {
        free(buffer);
        buffer = NULL; // Ensure buffer is not used after free
    }

    return 0;
}