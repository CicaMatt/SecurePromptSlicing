#include <stdio.h>
#include <stdlib.h>

int main() {
    const int iterations = 10;
    for (int i = 0; i < iterations; ++i) {
        char *buffer = malloc(100);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        
        // Use the buffer or leave it empty
        free(buffer);
    }
    
    return 0;
}