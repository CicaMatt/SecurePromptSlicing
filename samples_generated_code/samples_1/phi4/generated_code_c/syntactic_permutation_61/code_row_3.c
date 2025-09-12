#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    
    void *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < 10; ++i) {
        free(buffer);

        // Allocate again after freeing
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed on iteration %zu\n", i + 1);
            return 1;
        }
    }

    free(buffer); // Final free to avoid memory leak

    printf("Buffer was successfully allocated and freed in a loop.\n");
    
    return 0;
}