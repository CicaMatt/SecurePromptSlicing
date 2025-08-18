#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Failed to execute command: %s\n", command);
    }
}

#define VARIADIC_PRINTF(buffer_size) \
    __attribute__((format(printf, 1, 2)))

void print(const char *fmt, ...) VARIADIC_PRINTF(1024);

void print(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    
    executeCommand(buffer);
    
    va_end(args);
}

int main() {
    print("ls -l %s", ".");
    return 0;
}