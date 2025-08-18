#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    size_t bytesRead = fread(buf, 1, 100, stdin);

    if (bytesRead < 0) {
        free(buf);
        fprintf(stderr, "Error reading from standard input\n");
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    bytesRead = fread(buf1, 1, 100, stdin);

    if (bytesRead < 0) {
        free(buf);
        free(buf1);
        fprintf(stderr, "Error reading from standard input\n");
        return 1;
    }
    
    // Optionally print the buffers to verify
    buf[bytesRead] = '\0';
    buf1[bytesRead] = '\0';

    printf("Buffer 1: %s\n", buf);
    printf("Buffer 2: %s\n", buf1);

    free(buf);
    free(buf1);
    
    return 0;
}