#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *cmd) {
    int status = system(cmd);
    if (status == -1) {
        perror("Failed to execute command");
    }
}

int print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Create a buffer for the formatted string
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    printf("%s\n", buffer);
    va_end(args);

    // Execute the command formed by the print function
    executeCommand(buffer);

    return 0;
}

int main() {
    // Example usage of the print function
    print("ls -l %s", "/");  // Lists detailed information about files in root directory

    return 0;
}