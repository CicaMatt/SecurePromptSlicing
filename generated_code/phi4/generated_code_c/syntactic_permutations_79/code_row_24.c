#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf, *buf1;
    
    // Allocate 1024 bytes for buf
    buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Read up to 100 characters from stdin into buf
    size_t bytesRead = fread(buf, sizeof(char), 100, stdin);
    if (bytesRead < 0) {
        free(buf);
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    // Allocate 1024 bytes for buf1
    buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Read up to 100 characters from stdin into buf1
    bytesRead = fread(buf1, sizeof(char), 100, stdin);
    if (bytesRead < 0) {
        free(buf);
        free(buf1);
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    // Print the contents of both buffers for demonstration purposes
    printf("First buffer content: %.*s\n", (int)bytesRead, buf);
    printf("Second buffer content: %.*s\n", (int)bytesRead, buf1);

    // Free allocated memory
    free(buf);
    free(buf1);

    return 0;
}