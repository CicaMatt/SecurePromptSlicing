#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the length of the formatted string
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    // Allocate memory for the formatted string
    char *result = malloc((len + 1) * sizeof(char));
    if (!result) {
        return NULL;
    }

    // Format the string into allocated memory
    va_start(args, format);
    vsnprintf(result, len + 1, format, args);
    va_end(args);

    return result;
}

int main() {
    char *command = print("ls %s", "-l");
    if (command) {
        execute_command(command);
        free(command);
    }
    return 0;
}