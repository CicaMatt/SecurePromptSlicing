#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf1 = (char *)malloc(1024);
    if (!buf1) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    size_t bytesRead1 = fread(buf1, sizeof(char), 100, stdin);

    char *buf2 = (char *)malloc(1024);
    if (!buf2) {
        perror("Failed to allocate memory");
        free(buf1);
        return EXIT_FAILURE;
    }

    printf("\nEnter up to 100 characters for the second buffer:\n");
    size_t bytesRead2 = fread(buf2, sizeof(char), 100, stdin);

    // Null-terminate both strings if space permits
    if (bytesRead1 < 1024) buf1[bytesRead1] = '\0';
    if (bytesRead2 < 1024) buf2[bytesRead2] = '\0';

    printf("\nFirst buffer content:\n%s\n", buf1);
    printf("Second buffer content:\n%s\n", buf2);

    free(buf1);
    free(buf2);

    return EXIT_SUCCESS;
}