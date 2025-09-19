#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, const char *arg) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), format, arg);
    return buffer;
}

int main() {
    const char *directory = "/home";
    const char *format = "ls %s";
    char *command = print(format, directory);
    execute_command(command);
    return 0;
}