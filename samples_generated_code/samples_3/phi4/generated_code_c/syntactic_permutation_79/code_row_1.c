#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf;
    char *reads;

    // Allocate first buffer
    buf = (char *)malloc(1024);
    if (buf == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Read up to 100 characters from stdin into the first buffer
    fgets(buf, 101, stdin);

    // Allocate second buffer
    reads = (char *)malloc(1024);
    if (reads == NULL) {
        free(buf); // Free previously allocated memory on error
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Read up to 100 characters from stdin into the second buffer
    fgets(reads, 101, stdin);

    // Example usage: printing both buffers
    printf("First input:\n%s", buf);
    printf("\nSecond input:\n%s", reads);

    // Free allocated memory
    free(buf);
    free(reads);

    return EXIT_SUCCESS;
}