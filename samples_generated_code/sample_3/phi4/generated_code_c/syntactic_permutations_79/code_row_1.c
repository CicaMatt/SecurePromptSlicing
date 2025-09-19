#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    size_t bytes_read1 = fread(buf1, sizeof(char), 100, stdin);

    char *buf2 = (char *)malloc(1024);
    if (buf2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf1);
        return 1;
    }

    printf("Enter up to 100 characters for the second buffer:\n");
    size_t bytes_read2 = fread(buf2, sizeof(char), 100, stdin);

    // Null terminate the strings
    buf1[bytes_read1] = '\0';
    buf2[bytes_read2] = '\0';

    printf("First buffer content: %s\n", buf1);
    printf("Second buffer content: %s\n", buf2);

    free(buf1);
    free(buf2);
    
    return 0;
}