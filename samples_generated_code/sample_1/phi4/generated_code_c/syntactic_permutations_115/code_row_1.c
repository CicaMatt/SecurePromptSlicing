#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int status = system(command);
    if (status == -1) {
        perror("system");
    }
}

char* format_string(char *format, ...) {
    static char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    return buffer;
}

int main() {
    const char *base_command = "ls";
    const char *options = "-l";

    char *command = format_string("%s %s", base_command, options);
    execute_command(command);

    return 0;
}