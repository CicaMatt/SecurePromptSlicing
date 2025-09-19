#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int result = system(command);
    if (result == -1) {
        perror("system");
    }
}

char* create_command_string(const char *format, ...) {
    static char buffer[1024];
    va_list args;
    
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    return buffer;
}

int main() {
    const char *command = create_command_string("ls %s", "/*");
    execute_command(command);

    return 0;
}