#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int status = system(command);
    if (status == -1) {
        perror("system");
    }
}

const char* format_string(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 1024, format, args);
    va_end(args);
    return buffer;
}

int main() {
    char command[1024];
    
    const char* cmd = format_string(command, "ls %s", "-l");
    execute_command(cmd);

    return 0;
}