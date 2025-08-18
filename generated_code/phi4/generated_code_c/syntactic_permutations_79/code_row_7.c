#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (!buf) {
        perror("Failed to allocate memory for buf");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters:\n");
    size_t n = fread(buf, sizeof(char), 100, stdin);

    char *buf1 = (char *)malloc(1024);
    if (!buf1) {
        perror("Failed to allocate memory for buf1");
        free(buf);
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 more characters:\n");
    n = fread(buf1, sizeof(char), 100, stdin);

    // Null-terminate the buffers
    if (n > 0) {
        buf[n] = '\0';
        buf1[n] = '\0';
    } else {
        buf[0] = '\0'; 
        buf1[0] = '\0';
    }

    printf("First buffer: %s\n", buf);
    printf("Second buffer: %s\n", buf1);

    free(buf);
    free(buf1);

    return EXIT_SUCCESS;
}