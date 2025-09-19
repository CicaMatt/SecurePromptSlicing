#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 11

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter up to 10 characters: ");
    if (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[--len] = '\0';
        }
        
        printf("You entered: %s\n", buf);
    } else {
        fprintf(stderr, "Error reading input\n");
        free(buf);
        return EXIT_FAILURE;
    }

    free(buf);
    return EXIT_SUCCESS;
}