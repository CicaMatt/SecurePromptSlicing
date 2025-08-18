#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf); // Free previously allocated memory
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 1024 characters:\n");
    if (fgets(buf, 1025, stdin) != NULL) { // Read including newline character
        buf[strcspn(buf, "\n")] = '\0'; // Remove the trailing newline character
        printf("Input: %s\n", buf);
        
        // Copy input to buf1
        snprintf(buf1, sizeof(buf1), "%s", buf);
        printf("Copied to buf1: %s\n", buf1);
    } else {
        fprintf(stderr, "Error reading input\n");
    }

    free(buf);
    free(buf1);

    return 0;
}