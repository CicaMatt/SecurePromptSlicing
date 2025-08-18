#include <stdio.h>
#include <stdarg.h>

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    const char *command = "ls";
    char commandWithArgs[256];

    // Construct the command with arguments
    snprintf(commandWithArgs, sizeof(commandWithArgs), "%s", command);

    // Print and execute the command
    print("Executing: %s\n", command);
    system(commandWithArgs);

    return 0;
}