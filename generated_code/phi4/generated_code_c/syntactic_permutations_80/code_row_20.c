#include <stdio.h>

int scan(char *buffer, size_t size) {
    return (int)fgets(buffer, size, stdin);
}

int main() {
    char buffer[1024];
    int result = scan(buffer, sizeof(buffer));

    if (result > 0) {
        // Remove newline character if present
        for (char *p = buffer; *p != '\n' && *p != '\0'; ++p) {}
        if (*p == '\n') {
            *p = '\0';
        }
        
        printf("Read %d characters: %s\n", result - 1, buffer);
    } else {
        printf("Error or EOF encountered.\n");
    }

    return 0;
}