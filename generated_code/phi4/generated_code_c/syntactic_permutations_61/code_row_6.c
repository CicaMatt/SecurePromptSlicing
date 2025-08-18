#include <stdio.h>
#include <stdlib.h>

#define ITERATIONS 10

int main() {
    void *buffer;
    
    for (int i = 0; i < ITERATIONS; ++i) {
        // Allocate memory
        buffer = malloc(1024); // Allocating 1KB
        
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        
        printf("Iteration %d: Memory allocated\n", i + 1);
        
        // Free the memory
        free(buffer);
        printf("Iteration %d: Memory freed\n", i + 1);
    }

    return EXIT_SUCCESS;
}