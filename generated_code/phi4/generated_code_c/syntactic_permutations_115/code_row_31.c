#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    system(command);
}

int vprint(char **output, const char *format, va_list args) {
    size_t size = 256;
    char *buffer = malloc(size);

    if (!buffer)
        return -1;

    while (1) {
        va_list args_copy;
        va_copy(args_copy, args);
        int n = vsnprintf(buffer, size, format, args_copy);
        va_end(args_copy);

        if (n < 0 || n >= size) {
            free(buffer);
            size *= 2;
            buffer = realloc(buffer, size);
            if (!buffer)
                return -1;
        } else {
            break;
        }
    }

    *output = buffer;
    return 0;
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char *result = NULL;
    int status = vprint(&result, format, args);
    
    if (status == -1) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    va_end(args);
    return result;
}

int main() {
    const char *command = print("ls %s", "your_directory_here"); // Replace with actual directory
    execute_command(command);
    
    free((void*)command);  // Free the allocated memory for the command string
    return 0;
}