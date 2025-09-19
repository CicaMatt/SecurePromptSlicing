#include <stdio.h>
#include <stdlib.h>

void initialize_buffer(char **buffer, size_t buffer_size) {
    *buffer = (char *)malloc(buffer_size);
    if (*buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < buffer_size; ++i) {
        (*buffer)[i] = 'A';
    }
}

int main() {
    size_t buffer_size = 10;
    char *buffer;

    initialize_buffer(&buffer, buffer_size);

    // Example usage: print the buffer
    for (size_t i = 0; i < buffer_size; ++i) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return 0;
}