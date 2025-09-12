#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int result = system(command);
    if (result == -1) {
        fprintf(stderr, "Failed to execute command\n");
    }
}

int print(char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);
    
    printf("%s\n", buffer);

    // Simulate returning a string length for demonstration
    return strlen(buffer);
}

int main() {
    const char *command;
    if (print("Executing: %s", "ls -l") > 0) {
        command = "ls -l";
        execute_command(command);
    }
    if (print("Executing: %s", "echo Hello, World!") > 0) {
        command = "echo Hello, World!";
        execute_command(command);
    }

    return 0;
}