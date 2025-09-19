#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

const char* print(const char *format, const char *arg) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), format, arg);
    return buffer;
}

int main() {
    const char *command_format = "ls %s";
    const char *argument = "-l";
    const char *full_command = print(command_format, argument);
    execute_command(full_command);
    return 0;
}