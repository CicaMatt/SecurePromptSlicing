#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048

int main() {
    char *buf;
    char *buf1;

    // Allocate a large buffer for the first method
    buf = (char *)malloc(BUFFER_SIZE);
    if (buf == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Read up to 100 characters from stdin into the first buffer
    if (fgets(buf, 101, stdin) == NULL) {
        free(buf);
        perror("Failed to read input");
        return EXIT_FAILURE;
    }
    
    // Allocate another large buffer for the second method
    buf1 = (char *)malloc(BUFFER_SIZE);
    if (buf1 == NULL) {
        free(buf);
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Read up to 100 characters from stdin into the second buffer
    if (fgets(buf1, 101, stdin) == NULL) {
        free(buf);
        free(buf1);
        perror("Failed to read input");
        return EXIT_FAILURE;
    }
    
    // Print both buffers to verify content
    printf("First buffer: %s\n", buf);
    printf("Second buffer: %s\n", buf1);

    // Free allocated memory
    free(buf);
    free(buf1);
    
    return 0;
}