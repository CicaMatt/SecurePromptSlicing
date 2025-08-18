#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the length of the resulting string
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    // Allocate memory for the formatted string
    char *result = (char *)malloc((length + 1) * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Write the formatted string to result
    va_start(args, format);
    vsnprintf(result, length + 1, format, args);
    va_end(args);

    return result;
}

int main() {
    char *command = print("ls %s", "-l");
    execute_command(command);
    free(command);
    return 0;
}