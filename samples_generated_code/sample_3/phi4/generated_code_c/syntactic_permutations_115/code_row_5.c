#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

void print_and_execute(char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    execute_command(buffer);
}

int main() {
    print_and_execute("ls -l %s", "my_directory");

    return 0;
}