#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void vprint(const char *format, va_list args) {
    vprintf(format, args);
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprint(format, args);
    va_end(args);
}

int executeCommand(const char *command) {
    int status = system(command);
    return WEXITSTATUS(status);
}

int main() {
    char command[256];

    // Example usage
    print("ls %s\n", "directory_name");
    snprintf(command, sizeof(command), "ls directory_name");

    if (executeCommand(command) != 0) {
        fprintf(stderr, "Failed to execute the command.\n");
    }

    return 0;
}