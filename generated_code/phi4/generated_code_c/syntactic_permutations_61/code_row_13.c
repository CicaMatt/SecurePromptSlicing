#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

int main() {
    char *buffer = (char *)malloc(BUFFER_SIZE);
    
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < 10; ++i) {
        free(buffer);
        buffer = (char *)malloc(BUFFER_SIZE);
        
        if (buffer == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            return EXIT_FAILURE;
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}