#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int status = system(command);
    if (status == -1) {
        perror("system");
    }
}

void print_formatted(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    // Create command string
    const char *command = "ls";
    
    // Execute the command
    execute_command(command);

    // Use print function with a formatted string
    int number = 42;
    const char *text = "example";

    print_formatted("Formatted output: %s, %d\n", text, number);
    
    return 0;
}