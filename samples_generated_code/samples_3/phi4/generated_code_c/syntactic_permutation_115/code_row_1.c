#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *cmd) {
    char command[1024];
    snprintf(command, sizeof(command), "ls %s", cmd);
    int result = system(command);
    if (result != 0) {
        printf("Failed to execute command: ls %s\n", cmd);
    }
}

int print(char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    execute_command(buffer);

    va_end(args);
    return 0;
}

int main() {
    print("%s", "-l");
    print("%s %s", "-a", "/tmp");
    return 0;
}