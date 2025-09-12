#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main() {
    int i;
    char *buffer;

    for (i = 0; i < SIZE; ++i) {
        buffer = (char *)malloc(10);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        free(buffer);
    }

    return EXIT_SUCCESS;
}