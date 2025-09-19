#include <stdlib.h>
#include <stdio.h>

int main() {
    const int iterations = 10;
    char *buffer;

    for (int i = 0; i < iterations; ++i) {
        buffer = malloc(100 * sizeof(char));
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }

        // Simulate using the buffer
        snprintf(buffer, 100, "Iteration %d", i);

        free(buffer);
    }

    printf("Buffer allocated and freed successfully.\n");
    return 0;
}