#include <stdio.h>
#include <stdlib.h>

// Function to mimic printf behavior using variadic functions
void custom_print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

// Function to execute a command line utility with the generated string
void execute_command() {
    const char *command = "echo";
    const char *message = "\"Hello from command line!\"";
    
    // Using custom_print to create and execute a command string
    custom_print("%s %s\n", command, message);

    // Using system call to actually run the command
    int result = system(custom_print_command);
    if (result != 0) {
        fprintf(stderr, "Command execution failed!\n");
    }
}

int main() {
    execute_command();
    return 0;
}