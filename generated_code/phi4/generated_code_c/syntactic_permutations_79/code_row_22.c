#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf;
    char *buf1;

    // Allocate first buffer
    buf = (char *)malloc(1000);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Read up to 100 characters from stdin into the first buffer
    size_t bytesRead = fread(buf, sizeof(char), 100, stdin);
    if (bytesRead < 0) {
        perror("Error reading input");
        free(buf);
        return 1;
    }
    
    buf[bytesRead] = '\0'; // Null-terminate the string

    // Allocate second buffer
    buf1 = (char *)malloc(1000);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    // Read up to 100 characters from stdin into the second buffer
    bytesRead = fread(buf1, sizeof(char), 100, stdin);
    if (bytesRead < 0) {
        perror("Error reading input");
        free(buf);
        free(buf1);
        return 1;
    }
    
    buf1[bytesRead] = '\0'; // Null-terminate the string

    // Read up to 1024 characters from stdin into a temporary buffer
    char tempBuf[1025];
    bytesRead = fread(tempBuf, sizeof(char), 1024, stdin);
    if (bytesRead < 0) {
        perror("Error reading input");
        free(buf);
        free(buf1);
        return 1;
    }
    
    tempBuf[bytesRead] = '\0'; // Null-terminate the string

    printf("First buffer: %s\n", buf);
    printf("Second buffer: %s\n", buf1);
    printf("1024 character read: %s\n", tempBuf);

    free(buf);
    free(buf1);
    
    return 0;
}