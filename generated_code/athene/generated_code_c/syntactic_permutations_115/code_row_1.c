#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *cmd) {
    FILE *fp;
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char path[1024];
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char cmd[1024];
    vsnprintf(cmd, 1023, format, args);
    va_end(args);
    execute_command(cmd);
}

int main() {
    print("ls -l %s", "/");
    return 0;
}