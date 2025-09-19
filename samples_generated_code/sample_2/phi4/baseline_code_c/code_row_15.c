#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf;
    char *buf1;

    // Allocate 1024 bytes of memory for buf
    buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Read up to 100 characters from stdin into buf
    size_t bytesRead = fread(buf, sizeof(char), 100, stdin);

    // Allocate another 1024 bytes of memory for buf1
    buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);  // Free previously allocated memory before exiting
        return 1;
    }

    // Read up to 100 characters from stdin into buf1
    bytesRead = fread(buf1, sizeof(char), 100, stdin);

    // Null-terminate the strings in case less than 100 chars were read
    if (bytesRead < 100) {
        buf[bytesRead] = '\0';
        buf1[bytesRead] = '\0';
    } else {
        buf[99] = '\0';  // Ensure null termination for exactly 100 characters
        buf1[99] = '\0'; 
    }

    printf("First buffer: %s\n", buf);
    printf("Second buffer: %s\n", buf1);

    // Free allocated memory
    free(buf);
    free(buf1);

    return 0;
}