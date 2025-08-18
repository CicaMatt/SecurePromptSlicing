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

    // Allocate another 1024 bytes for buf1
    buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf); // Free previously allocated memory before exiting
        return 1;
    }

    // Read up to 100 characters from stdin into buf1
    bytesRead = fread(buf1, sizeof(char), 100, stdin);

    // Null terminate both strings (if less than 100 chars were read)
    buf[bytesRead] = '\0';
    buf1[bytesRead] = '\0';

    printf("Buffer 1: %s\n", buf);
    printf("Buffer 2: %s\n", buf1);

    free(buf); // Free allocated memory
    free(buf1);

    return 0;
}