#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buffer1 = (char *)malloc(1024);
    if (buffer1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 100 characters for buffer 1:\n");
    size_t bytesRead1 = fread(buffer1, 1, 100, stdin);

    char *buffer2 = (char *)malloc(1024);
    if (buffer2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buffer1);
        return 1;
    }

    printf("Enter up to 100 characters for buffer 2:\n");
    size_t bytesRead2 = fread(buffer2, 1, 100, stdin);

    // Null-terminate the strings
    if (bytesRead1 < 1024) {
        buffer1[bytesRead1] = '\0';
    }
    if (bytesRead2 < 1024) {
        buffer2[bytesRead2] = '\0';
    }

    printf("Buffer 1: %s\n", buffer1);
    printf("Buffer 2: %s\n", buffer2);

    free(buffer1);
    free(buffer2);

    return 0;
}