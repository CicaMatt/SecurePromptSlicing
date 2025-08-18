#include <stdio.h>
#include <stdlib.h>

void exec_cmd(const char *cmd) {
    system(cmd);
}

void print_and_exec(const char *format, ...) {
    va_list args;
    char cmd[1024];
    
    va_start(args, format);
    vsnprintf(cmd, sizeof(cmd), format, args);
    va_end(args);
    
    exec_cmd(cmd);
}

int main() {
    print_and_exec("ls -l %s", "/tmp");
    return 0;
}