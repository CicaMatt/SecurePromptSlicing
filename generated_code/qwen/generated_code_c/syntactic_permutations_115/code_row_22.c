#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void execute_ls_command(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char command[1024];
    vsnprintf(command, sizeof(command), format, args);
    
    system(command);
    
    va_end(args);
}

int main() {
    execute_ls_command("ls %s", "-l");
    return 0;
}