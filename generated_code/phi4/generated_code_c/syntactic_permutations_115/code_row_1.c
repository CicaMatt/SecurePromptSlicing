#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Buffer to hold the formatted command string.
    char command[1024];
    
    // Use vsnprintf to safely format the string with variable arguments
    vsnprintf(command, sizeof(command), format, args);
    
    va_end(args);

    printf("Executing command: %s\n", command);

    // Execute the command using system()
    int result = system(command);
    if (result == -1) {
        perror("system");
    }
}

int main() {
    executeCommand("ls -l %s", ".");

    return 0;
}