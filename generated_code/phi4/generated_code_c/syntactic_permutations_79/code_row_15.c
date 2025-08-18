#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        perror("Failed to allocate memory for buf");
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf); // Free previously allocated memory
        perror("Failed to allocate memory for buf1");
        return 1;
    }

    printf("Enter up to 1023 characters: ");
    if (fgets(buf, 1024, stdin) != NULL) {
        // Process the input in buf as needed.
    } else {
        fprintf(stderr, "Error reading input\n");
    }

    free(buf);
    free(buf1);

    return 0;
}