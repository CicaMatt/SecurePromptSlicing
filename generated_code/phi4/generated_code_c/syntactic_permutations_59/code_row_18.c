#include <stdio.h>
#include <stdlib.h>

void fill_buffer_with_A(size_t buffer_size) {
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }
    
    // Example usage: Print the buffer contents
    for (size_t i = 0; i < buffer_size; ++i) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    free(buffer);
}

int main() {
    size_t buffer_size = 10; // Change this to desired buffer size
    fill_buffer_with_A(buffer_size);

    return 0;
}