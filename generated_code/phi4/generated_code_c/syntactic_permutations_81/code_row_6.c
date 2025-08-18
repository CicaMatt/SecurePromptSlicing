#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 11 // 10 characters + null terminator

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 10 characters: ");
    if (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }
        
        printf("Stored characters: %s\n", buf);
    } else {
        fprintf(stderr, "Failed to read input\n");
        free(buf);
        return 1;
    }

    free(buf);
    return 0;
}