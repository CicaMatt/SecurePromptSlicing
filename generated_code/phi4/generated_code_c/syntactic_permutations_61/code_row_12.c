#include <stdio.h>
#include <stdlib.h>

int main() {
    int buffer_size;
    
    printf("Enter buffer size: ");
    scanf("%d", &buffer_size);
    
    if (buffer_size <= 0) {
        fprintf(stderr, "Buffer size must be greater than zero.\n");
        return EXIT_FAILURE;
    }
    
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    
    printf("Buffer allocated successfully. Size: %d\n", buffer_size);
    
    // Example of using the buffer
    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26); // Fill with letters A-Z
    }
    
    printf("Buffer content:\n");
    for (int i = 0; i < buffer_size; ++i) {
        putchar(buffer[i]);
        if ((i+1) % 10 == 0) { // Newline every 10 characters for better readability
            putchar('\n');
        }
    }

    free(buffer);
    
    return EXIT_SUCCESS;
}