#include <stdio.h>
#include <stdlib.h>

void allocate_and_fill_buffer(size_t buffer_size) {
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }
    
    // Example usage: print the buffer
    printf("Buffer contents:\n%s\n", buffer);

    free(buffer);
}

int main() {
    size_t buffer_size;
    printf("Enter buffer size: ");
    if (scanf("%zu", &buffer_size) != 1 || buffer_size == 0) {
        fprintf(stderr, "Invalid input for buffer size.\n");
        return 1;
    }
    
    allocate_and_fill_buffer(buffer_size);
    return 0;
}