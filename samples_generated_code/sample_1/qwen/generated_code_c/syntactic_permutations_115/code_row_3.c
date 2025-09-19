#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

void print(char **output, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vasprintf(output, format, args);
    va_end(args);
}

int main() {
    char *command = NULL;
    print(&command, "ls %s", "-l");
    execute_command(command);
    free(command);
    return 0;
}