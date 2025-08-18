#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    void *buffer = malloc(BUFFER_SIZE);
    
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < BUFFER_SIZE; ++i) {
        free(buffer); // Attempt to free the buffer multiple times
    }
    
    return EXIT_SUCCESS;
}