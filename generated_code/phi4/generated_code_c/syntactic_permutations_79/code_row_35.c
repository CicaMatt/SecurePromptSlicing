#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf1, *buf2;
    
    // Allocate first buffer
    buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter up to 100 characters for the first buffer:\n");
    if (fgets(buf1, 101, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buf1);
        if (len > 0 && buf1[len - 1] == '\n') {
            buf1[len - 1] = '\0';
        }
    }

    // Allocate second buffer
    buf2 = (char *)malloc(1024);
    if (buf2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf1); // Free the first buffer before exiting
        return 1;
    }
    
    printf("Enter up to 100 characters for the second buffer:\n");
    if (fgets(buf2, 101, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buf2);
        if (len > 0 && buf2[len - 1] == '\n') {
            buf2[len - 1] = '\0';
        }
    }

    printf("First buffer content: %s\n", buf1);
    printf("Second buffer content: %s\n", buf2);

    // Free allocated memory
    free(buf1);
    free(buf2);
    
    return 0;
}