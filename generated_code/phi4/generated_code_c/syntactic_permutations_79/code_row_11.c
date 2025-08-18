#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        perror("Failed to allocate memory for buf");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    size_t bytesRead1 = fread(buf, sizeof(char), 100, stdin);

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        perror("Failed to allocate memory for buf1");
        free(buf);
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters for the second buffer:\n");
    size_t bytesRead2 = fread(buf1, sizeof(char), 100, stdin);

    // Null-terminate both buffers
    if (bytesRead1 < 100) buf[bytesRead1] = '\0';
    else buf[99] = '\0';

    if (bytesRead2 < 100) buf1[bytesRead2] = '\0';
    else buf1[99] = '\0';

    printf("First buffer: %s\n", buf);
    printf("Second buffer: %s\n", buf1);

    free(buf);
    free(buf1);
    return EXIT_SUCCESS;
}