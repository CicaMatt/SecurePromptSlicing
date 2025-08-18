#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *buf1 = (char *)malloc(BUFFER_SIZE);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    size_t bytes_read1 = fread(buf, sizeof(char), 100, stdin);

    printf("Enter up to 100 characters for the second buffer:\n");
    size_t bytes_read2 = fread(buf1, sizeof(char), 100, stdin);

    // Null-terminate strings
    buf[bytes_read1] = '\0';
    buf1[bytes_read2] = '\0';

    printf("First Buffer: %s\n", buf);
    printf("Second Buffer: %s\n", buf1);

    free(buf);
    free(buf1);
    
    return 0;
}