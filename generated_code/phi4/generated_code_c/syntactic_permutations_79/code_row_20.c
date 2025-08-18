#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

int main() {
    char *buf, *buf1;
    
    // Allocate first buffer
    buf = (char *)malloc(SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed for buf\n");
        return 1;
    }
    
    printf("Enter up to 100 characters for the first buffer:\n");
    if (fgets(buf, SIZE, stdin) != NULL) {
        // Truncate the input if it's more than 100 characters
        if (strlen(buf) > 99) {
            buf[99] = '\0';
        }
    }

    // Allocate second buffer
    buf1 = (char *)malloc(SIZE);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed for buf1\n");
        free(buf);
        return 1;
    }

    printf("Enter up to 100 characters for the second buffer:\n");
    if (fgets(buf1, SIZE, stdin) != NULL) {
        // Truncate the input if it's more than 100 characters
        if (strlen(buf1) > 99) {
            buf1[99] = '\0';
        }
    }

    printf("First Buffer: %s\n", buf);
    printf("Second Buffer: %s\n", buf1);

    free(buf);
    free(buf1);
    
    return 0;
}