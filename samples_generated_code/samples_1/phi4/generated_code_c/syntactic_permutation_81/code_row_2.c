#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(11); // Allocate memory for 10 characters + null terminator
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter up to 10 characters:\n");
    if (fgets(buf, 11, stdin) != NULL) { // Read up to 10 characters and a newline
        size_t len = strlen(buf);
        if (buf[len - 1] == '\n') {
            buf[len - 1] = '\0'; // Replace newline with null terminator if present
        }
    } else {
        free(buf); // Free memory on read failure
        return 1;
    }

    printf("You entered: %s\n", buf);

    free(buf); // Free allocated memory
    return 0;
}