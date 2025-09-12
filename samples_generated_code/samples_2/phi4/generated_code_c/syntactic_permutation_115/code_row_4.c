#include <stdio.h>
#include <stdlib.h>

int execute_command(const char *command) {
    int status = system(command);
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

void print_and_execute(const char *format, ...) {
    char buffer[1024];
    va_list args;
    
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    printf("Executing: %s\n", buffer);
    int status = execute_command(buffer);

    if (status == -1) {
        fprintf(stderr, "Failed to execute command.\n");
    } else {
        printf("Command executed with exit status: %d\n", status);
    }
}

int main() {
    print_and_execute("ls -l %s", "/"); // Example usage
    return 0;
}