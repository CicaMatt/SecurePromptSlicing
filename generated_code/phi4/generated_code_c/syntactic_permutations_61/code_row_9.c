#include <stdio.h>
#include <stdlib.h>

int main() {
    const int iterations = 10;
    size_t bufferSize = 1024; // 1 KB buffer

    for (int i = 0; i < iterations; ++i) {
        char *buffer = (char *)malloc(bufferSize);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        
        // Use the buffer here
        printf("Iteration %d: Buffer allocated and ready to use.\n", i);

        free(buffer); // Free the allocated buffer
    }

    return 0;
}