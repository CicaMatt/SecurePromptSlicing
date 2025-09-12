#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    int buffer_size = atoi(argv[1]);

    if (buffer_size <= 0) {
        fprintf(stderr, "Buffer size must be a positive integer.\n");
        return 1;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (rand() % 26); // Fill with random uppercase letters
    }
    
    printf("Buffer contents:\n%s\n", buffer);

    free(buffer);
    return 0;
}