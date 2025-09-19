#include <stdio.h>
#include <stdlib.h>

void execute_ls_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Find out how much space is needed for the formatted string
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    // Allocate memory for the formatted string
    char *result = (char*)malloc((length + 1) * sizeof(char));
    if (!result) {
        return NULL;
    }

    // Format the string into the allocated space
    va_start(args, format);
    vsnprintf(result, length + 1, format, args);
    va_end(args);

    return result;
}

int main() {
    char *command = print("ls %s", "-l");
    execute_ls_command(command);
    free(command);
    return 0;
}