#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Find out how much space is needed
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    // Allocate memory for the string
    char *output = (char*)malloc((length + 1) * sizeof(char));
    if (!output) {
        return NULL;
    }

    // Write the formatted string to the allocated buffer
    va_start(args, format);
    vsnprintf(output, length + 1, format, args);
    va_end(args);

    return output;
}

int main() {
    char *command = print("ls %s", "-l");
    if (command) {
        execute_command(command);
        free(command);
    }
    return 0;
}