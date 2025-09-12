#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate length of formatted string
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    // Allocate memory for the formatted string
    char *str = (char *)malloc((len + 1) * sizeof(char));
    if (!str) {
        return NULL;
    }

    // Format the string into allocated buffer
    va_start(args, format);
    vsnprintf(str, len + 1, format, args);
    va_end(args);

    return str;
}

int main() {
    char *command = print("ls %s", "-l");
    if (command) {
        execute_command(command);
        free(command);
    }
    return 0;
}