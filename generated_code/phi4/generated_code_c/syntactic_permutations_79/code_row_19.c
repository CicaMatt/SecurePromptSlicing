#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (!buf) {
        perror("Failed to allocate memory for buf");
        return EXIT_FAILURE;
    }

    char *buf1 = (char *)malloc(1024);
    if (!buf1) {
        free(buf);  // Free previously allocated memory
        perror("Failed to allocate memory for buf1");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters:\n");
    fgets(buf, 101, stdin);

    printf("Enter another up to 100 characters:\n");
    fgets(buf1, 101, stdin);

    // Output the contents of both buffers
    printf("First buffer content: %s", buf);
    printf("Second buffer content: %s", buf1);

    free(buf);
    free(buf1);
    return EXIT_SUCCESS;
}