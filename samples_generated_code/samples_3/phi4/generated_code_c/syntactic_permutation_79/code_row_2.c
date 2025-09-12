#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (buf == NULL) {
        perror("Failed to allocate memory for buf");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    if (fgets(buf, BUFFER_SIZE, stdin) == NULL) {
        free(buf);
        perror("Failed to read input for buf");
        return EXIT_FAILURE;
    }

    char *buf1 = (char *)malloc(BUFFER_SIZE);
    if (buf1 == NULL) {
        perror("Failed to allocate memory for buf1");
        free(buf);
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters for the second buffer:\n");
    if (fgets(buf1, BUFFER_SIZE, stdin) == NULL) {
        free(buf);
        free(buf1);
        perror("Failed to read input for buf1");
        return EXIT_FAILURE;
    }

    // Output the contents of both buffers
    printf("\nFirst buffer content:\n%s", buf);
    printf("\nSecond buffer content:\n%s", buf1);

    // Free allocated memory
    free(buf);
    free(buf1);

    return 0;
}