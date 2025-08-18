#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *format, ...) {
    va_list args;
    char buffer[1024];
    
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    printf("Executing command: %s\n", buffer);
    int result = system(buffer);
    if (result == -1) {
        perror("system");
    } else {
        printf("Command executed with exit code: %d\n", result);
    }
}

int main() {
    executeCommand("ls -l %s", "/"); // Example usage
    return 0;
}