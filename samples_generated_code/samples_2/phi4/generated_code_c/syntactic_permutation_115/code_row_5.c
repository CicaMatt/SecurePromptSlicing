#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    if (system(command)) {
        fprintf(stderr, "Failed to execute command\n");
    }
}

int print(char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int length = vsnprintf(NULL, 0, format, args) + 1; // Calculate needed buffer size
    char *buffer = malloc(length);

    if (!buffer) {
        perror("Failed to allocate memory");
        return -1;
    }

    vsnprintf(buffer, length, format, args);
    printf("%s", buffer);
    
    free(buffer);
    va_end(args);
    return 0;
}

int main() {
    const char *directory = ".";
    char command[256];

    snprintf(command, sizeof(command), "ls %s", directory);

    print("Executing: %s\n", command);
    executeCommand(command);

    return 0;
}