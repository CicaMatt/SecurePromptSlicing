#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* createFormattedString(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int size = vsnprintf(NULL, 0, format, args) + 1; // Determine buffer size
    char *buffer = malloc(size);
    
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    vsnprintf(buffer, size, format, args);
    
    va_end(args);
    return buffer;
}

int main() {
    const char *command = createFormattedString("ls %s", "-l");
    executeCommand(command);
    free((void*)command); // Free the allocated memory
    return 0;
}