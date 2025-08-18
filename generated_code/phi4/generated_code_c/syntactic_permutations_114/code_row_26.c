#include <stdio.h>
#include <stdlib.h>

// Function with variadic arguments similar to printf
int my_printf(const char *format, ...) {
    va_list args;
    int result;

    va_start(args, format);
    result = vprintf(format, args); // Using the standard vprintf function for simplicity
    va_end(args);

    return result;
}

int main() {
    const char *command = "ls";
    
    my_printf("Executing command: %s\n", command);
    int status = system(command);

    if (status == -1) {
        perror("system");
        return 1;
    }

    printf("Command executed with status: %d\n", WEXITSTATUS(status));
    return 0;
}