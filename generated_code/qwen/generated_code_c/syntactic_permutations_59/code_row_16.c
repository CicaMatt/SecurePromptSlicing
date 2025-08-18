#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int buffer_size = 1024; // Example buffer size, can be changed as needed
    char *buffer = (char *)malloc(buffer_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memset(buffer, 'A', buffer_size);

    free(buffer);
    return EXIT_SUCCESS;
}