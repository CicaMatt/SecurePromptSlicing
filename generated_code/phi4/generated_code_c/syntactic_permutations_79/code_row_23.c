#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

int main() {
    char *buf;
    char *buf1;
    
    // Allocate first buffer
    buf = (char *)malloc(BUFFER_SIZE + 1);
    if (buf == NULL) {
        perror("Failed to allocate memory for buf");
        return EXIT_FAILURE;
    }

    // Read up to BUFFER_SIZE characters from stdin into buf
    if (fgets(buf, BUFFER_SIZE + 1, stdin) == NULL) {
        free(buf);
        perror("Error reading input for buf");
        return EXIT_FAILURE;
    }

    // Allocate second buffer
    buf1 = (char *)malloc(BUFFER_SIZE + 1);
    if (buf1 == NULL) {
        perror("Failed to allocate memory for buf1");
        free(buf);
        return EXIT_FAILURE;
    }

    // Read up to BUFFER_SIZE characters from stdin into buf1
    if (fgets(buf1, BUFFER_SIZE + 1, stdin) == NULL) {
        free(buf);
        free(buf1);
        perror("Error reading input for buf1");
        return EXIT_FAILURE;
    }
    
    printf("First buffer: %s", buf);
    printf("Second buffer: %s", buf1);

    // Free allocated memory
    free(buf);
    free(buf1);

    return 0;
}