#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the length of the formatted string
    int len = vsnprintf(NULL, 0, format, args);
    if (len < 0) {
        va_end(args);
        return NULL;
    }

    // Allocate memory for the formatted string
    char *formatted_string = malloc(len + 1);
    if (!formatted_string) {
        va_end(args);
        return NULL;
    }

    // Format the string into the allocated memory
    vsnprintf(formatted_string, len + 1, format, args);

    va_end(args);
    return formatted_string;
}

int main() {
    char *command = print("ls %s", "-l");
    if (command) {
        execute_command(command);
        free(command);
    }
    return 0;
}