#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int status = system(command);
    if (status == -1) {
        perror("system");
        exit(EXIT_FAILURE);
    }
}

char* create_format_string(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the length of the resulting string
    size_t len = vsnprintf(NULL, 0, format, args) + 1; // +1 for null terminator

    // Allocate memory for the formatted string
    char *result = (char *)malloc(len);
    if (!result) {
        perror("malloc");
        va_end(args);
        exit(EXIT_FAILURE);
    }

    // Create the formatted string
    vsnprintf(result, len, format, args);

    va_end(args);
    return result;
}

int main() {
    char *command = create_format_string("ls %s", "directory_name"); // Replace 'directory_name' with desired directory or use ""
    execute_command(command);

    free(command); // Free the allocated memory
    return 0;
}