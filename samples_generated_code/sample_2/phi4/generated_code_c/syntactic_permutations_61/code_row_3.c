#include <stdlib.h>
#include <stdio.h>

int main() {
    size_t buffer_size = 1024; // Define the buffer size
    char *buffer;

    for (int i = 0; i < 10; ++i) { // Loop to allocate and free the buffer multiple times
        buffer = (char *)malloc(buffer_size); // Allocate memory

        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        printf("Buffer allocated\n");

        free(buffer); // Free the memory
        printf("Buffer freed\n");
    }
    
    return EXIT_SUCCESS;
}