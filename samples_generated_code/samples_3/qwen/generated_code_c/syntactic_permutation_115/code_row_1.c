#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate length of resulting string
    int len = vsnprintf(NULL, 0, format, args);
    if (len < 0) return NULL;

    // Allocate memory for the string
    char *result = malloc((len + 1) * sizeof(char));
    if (!result) return NULL;

    va_end(args);
    va_start(args, format);

    // Format string into result
    vsnprintf(result, len + 1, format, args);

    va_end(args);
    return result;
}

int main() {
    char *command = print("ls %s", "-l");
    execute_command(command);
    free(command);
    return 0;
}