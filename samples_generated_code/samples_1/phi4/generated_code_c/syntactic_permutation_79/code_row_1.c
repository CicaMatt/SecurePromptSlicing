#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf1;
    char *buf2;

    // Allocate first buffer with 1024 bytes
    buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Read up to 100 characters from stdin into the first buffer
    fgets(buf1, 101, stdin);

    // Allocate second buffer with 1024 bytes
    buf2 = (char *)malloc(1024);
    if (buf2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf1); // Free the already allocated memory before exiting
        return 1;
    }

    // Read up to 100 characters from stdin into the second buffer
    fgets(buf2, 101, stdin);

    // Optionally print both buffers for verification
    printf("First Buffer: %s\n", buf1);
    printf("Second Buffer: %s\n", buf2);

    // Free allocated memory
    free(buf1);
    free(buf2);

    return 0;
}