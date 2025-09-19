#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        perror("Failed to allocate memory for buf");
        return EXIT_FAILURE;
    }

    char *buf1 = malloc(1024);
    if (buf1 == NULL) {
        perror("Failed to allocate memory for buf1");
        free(buf); // Free previously allocated memory
        return EXIT_FAILURE;
    }

    printf("Enter up to 1024 characters:\n");
    if (fgets(buf, 1025, stdin) != NULL) { // Use 1025 to read the newline character as well
        strncpy(buf1, buf, 100); // Copy first 100 characters from buf to buf1

        // Null-terminate buf1 in case we copied less than 100 characters
        buf1[99] = '\0';
    }

    printf("First 100 characters copied into buf1: %s\n", buf1);

    free(buf);
    free(buf1);

    return EXIT_SUCCESS;
}