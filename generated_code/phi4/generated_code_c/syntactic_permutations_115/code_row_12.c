#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int status = system(command);
    if (status == -1) {
        perror("system");
        exit(EXIT_FAILURE);
    }
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the size of the formatted string
    int size = vsnprintf(NULL, 0, format, args) + 1; // +1 for '\0'
    
    if (size <= 0) {
        va_end(args);
        return NULL;
    }

    char *str = malloc(size);

    if (!str) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    vsnprintf(str, size, format, args);
    va_end(args);
    return str;
}

int main() {
    const char* ls_command = print("ls %s", "-l");

    if (ls_command != NULL) {
        execute_command(ls_command);
        free((void*) ls_command);
    }

    return 0;
}