#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(11); // Allocate memory for 10 chars + null terminator
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter 10 characters: ");
    if (fgets(buf, 11, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }
        
        printf("Buffer content: %s\n", buf);
    } else {
        fprintf(stderr, "Error reading input\n");
        free(buf);
        return 1;
    }

    free(buf); // Free the allocated memory
    return 0;
}