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
        free(buf); // Free the previously allocated buffer
        return 1;
    }
    
    printf("Enter up to 100 characters for buf:\n");
    size_t read_count = fread(buf, sizeof(char), BUFFER_SIZE, stdin);
    if (ferror(stdin)) {
        fprintf(stderr, "Error reading from stdin\n");
        free(buf);
        free(buf1);
        return 1;
    }

    printf("Enter up to 100 characters for buf1:\n");
    read_count = fread(buf1, sizeof(char), BUFFER_SIZE, stdin);
    if (ferror(stdin)) {
        fprintf(stderr, "Error reading from stdin\n");
        free(buf);
        free(buf1);
        return 1;
    }

    // Null-terminate the strings
    buf[read_count < BUFFER_SIZE ? read_count : BUFFER_SIZE - 1] = '\0';
    buf1[read_count < BUFFER_SIZE ? read_count : BUFFER_SIZE - 1] = '\0';

    printf("Content of buf:\n%s\n", buf);
    printf("Content of buf1:\n%s\n", buf1);

    free(buf);
    free(buf1);
    
    return 0;
}