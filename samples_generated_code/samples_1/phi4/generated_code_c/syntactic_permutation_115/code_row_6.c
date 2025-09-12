#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void executeCommand(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Buffer to hold the formatted command
    char command[1024];
    vsnprintf(command, sizeof(command), format, args);

    va_end(args);

    // Execute the command using system()
    int result = system(command);
    
    if (result != 0) {
        fprintf(stderr, "Error executing command\n");
    }
}

int main() {
    // Example usage of executeCommand
    char *directory = ".";
    char *options[] = {"-l", "-a"};
    size_t numOptions = sizeof(options) / sizeof(options[0]);

    // Construct the format string for ls with options
    char formatString[256] = "ls ";
    for (size_t i = 0; i < numOptions; ++i) {
        strcat(formatString, "%s ");
    }
    
    // Execute the command with arguments
    executeCommand(formatString, directory, options[0], options[1]);

    return 0;
}