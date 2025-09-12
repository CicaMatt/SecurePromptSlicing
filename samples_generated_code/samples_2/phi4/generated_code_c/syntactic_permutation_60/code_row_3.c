#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = atoll(argv[1]);
    
    if (buffer_size == 0) {
        fprintf(stderr, "Buffer size must be greater than zero.\n");
        return 1;
    }
    
    char *buffer = (char *)malloc(buffer_size);
    
    if (!buffer) {
        perror("Failed to allocate buffer");
        return 1;
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26); // Fill with some pattern
    }
    
    printf("Buffer contents:\n%s\n", buffer);

    free(buffer);
    return 0;
}