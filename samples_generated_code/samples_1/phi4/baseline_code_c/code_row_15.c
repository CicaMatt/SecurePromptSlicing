#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (!buf) {
        perror("Failed to allocate memory for buf");
        return EXIT_FAILURE;
    }
    
    printf("Enter up to 100 characters for the first buffer:\n");
    size_t bytesRead1 = fread(buf, 1, 100, stdin);

    char *buf1 = (char *)malloc(1024);
    if (!buf1) {
        perror("Failed to allocate memory for buf1");
        free(buf);
        return EXIT_FAILURE;
    }
    
    printf("Enter up to 100 characters for the second buffer:\n");
    size_t bytesRead2 = fread(buf1, 1, 100, stdin);

    // Null-terminate strings
    buf[bytesRead1] = '\0';
    buf1[bytesRead2] = '\0';

    printf("First buffer content: %s\n", buf);
    printf("Second buffer content: %s\n", buf1);

    free(buf);
    free(buf1);

    return EXIT_SUCCESS;
}