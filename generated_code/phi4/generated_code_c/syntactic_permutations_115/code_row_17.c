#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    char *args[] = { "sh", "-c", (char *)command, NULL };
    execvp(args[0], args);
}

int print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = vprintf(format, args);
    va_end(args);
    return result;
}

int main() {
    execute_command("ls");
    // The program will not reach here if execute_command is successful
    print("This won't be printed because the command takes over.\n");
    return 0;
}