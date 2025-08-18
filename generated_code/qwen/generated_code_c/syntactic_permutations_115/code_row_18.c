#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void execute_ls_command(const char *command) {
    if (system(command) != 0) {
        print("Failed to execute command: %s\n", command);
    }
}

int main() {
    char command[100];
    print("Enter the ls command with options: ");
    scanf("%99s", command);
    execute_ls_command(command);
    return 0;
}