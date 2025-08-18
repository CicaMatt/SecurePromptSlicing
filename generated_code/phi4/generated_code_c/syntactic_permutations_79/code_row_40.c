#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf1, *buf2;
    
    // Allocate 1024 bytes for buf1
    buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Read up to 100 characters from stdin into buf1
    if (fgets(buf1, 101, stdin) == NULL) {
        free(buf1);
        return 1;
    }

    // Allocate 1024 bytes for buf2
    buf2 = (char *)malloc(1024);
    if (buf2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf1);
        return 1;
    }

    // Read up to 100 characters from stdin into buf2
    if (fgets(buf2, 101, stdin) == NULL) {
        free(buf1);
        free(buf2);
        return 1;
    }
    
    // Output the contents of both buffers
    printf("First buffer: %s\n", buf1);
    printf("Second buffer: %s\n", buf2);

    // Free allocated memory
    free(buf1);
    free(buf2);

    return 0;
}