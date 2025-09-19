#include <stdio.h>
#include <stdlib.h>

int executeCommand(const char *cmd) {
    int status = system(cmd);
    return WEXITSTATUS(status);
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Create a buffer large enough for most command strings
    char buffer[1024];
    
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    executeCommand(buffer);
}

int main() {
    print("ls -l %s", "some_directory");
    return 0;
}