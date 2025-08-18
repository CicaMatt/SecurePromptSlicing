#include <stdio.h>

int scan(char *buffer, int max_size) {
    if (buffer == NULL || max_size <= 0) {
        return -1;
    }

    // Read a line from standard input up to max_size-1 characters
    if (fgets(buffer, max_size, stdin) != NULL) {
        size_t length = strlen(buffer);
        
        // If the buffer contains newline character, remove it
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        return length;
    }
    
    return -1;
}

int main() {
    char buffer[1024];
    int result = scan(buffer, sizeof(buffer));
    
    if (result != -1) {
        printf("Read string: %s\n", buffer);
        printf("Number of characters read: %d\n", result);
    } else {
        printf("Failed to read input.\n");
    }
    
    return 0;
}