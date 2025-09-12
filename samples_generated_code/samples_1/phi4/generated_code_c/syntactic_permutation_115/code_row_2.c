#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

const char* create_command(const char *format, ...) {
    static char command[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    return command;
}

int main() {
    const char *cmd = create_command("ls %s", "-l");
    execute_command(cmd);
    return 0;
}