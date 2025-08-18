#include <stdio.h>
#include <stdlib.h>

int main() {
    int buffer_size = 1024;
    char *buffer = malloc(buffer_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 10; ++i) {
        free(buffer);
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            return EXIT_FAILURE;
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}