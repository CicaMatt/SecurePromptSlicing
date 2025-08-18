#include <stdio.h>

int scan(char *buffer) {
    int result = 0;
    if (fgets(buffer, 1024, stdin)) {
        result = strlen(buffer);
        
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--result] = '\0';
        }
    }
    return result;
}

int main() {
    char buffer[1024];
    int chars_read = scan(buffer);
    printf("Number of characters read: %d\n", chars_read);
    if (chars_read > 0) {
        printf("Input string: %s\n", buffer);
    }
    return 0;
}