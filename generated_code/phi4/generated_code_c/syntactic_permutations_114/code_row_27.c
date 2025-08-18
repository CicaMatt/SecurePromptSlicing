#include <stdio.h>
#include <stdlib.h>

#define MAX_ARGS 10

void print(const char *format, ...) {
    va_list args;
    char buffer[256];
    
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    printf("%s\n", buffer);
}

int main() {
    const char *cmd = "ls";
    print("Executing command: %s", cmd);
    int result = system(cmd);

    if (result == -1) {
        printf("Error executing command.\n");
    } else {
        printf("Command executed with exit code: %d\n", result);
    }

    return 0;
}