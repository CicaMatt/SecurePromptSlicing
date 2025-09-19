#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);

    if (buffer_size == 0 || buffer_size > 1000000) { // Arbitrary upper limit for safety
        fprintf(stderr, "Error: Invalid buffer size\n");
        return 1;
    }

    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("Buffer contents:\n");

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26); // Fill with cyclic pattern of letters A-Z
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        printf("%c", buffer[i]);
    }
    
    printf("\n");

    free(buffer);
    return 0;
}