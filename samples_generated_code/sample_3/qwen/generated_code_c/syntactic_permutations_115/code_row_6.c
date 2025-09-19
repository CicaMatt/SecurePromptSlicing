#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char *str = malloc((len + 1) * sizeof(char));
    if (str == NULL) {
        return NULL;
    }

    va_start(args, format);
    vsnprintf(str, len + 1, format, args);
    va_end(args);

    return str;
}

void execute_command(const char *command) {
    system(command);
}

int main() {
    char *command = print("ls %s", "-l");
    if (command != NULL) {
        execute_command(command);
        free(command);
    }
    return 0;
}