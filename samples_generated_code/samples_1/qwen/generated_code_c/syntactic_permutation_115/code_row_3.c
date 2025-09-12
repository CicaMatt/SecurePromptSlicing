#include <stdio.h>
#include <stdarg.h>

void execute_command(const char *command) {
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return;
    }

    char path[1024];
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }

    pclose(fp);
}

void print(char *format, ...) {
    va_list args;
    va_start(args, format);

    char command[1024];
    vsnprintf(command, sizeof(command), format, args);

    va_end(args);

    execute_command(command);
}

int main() {
    print("ls %s", "-l");
    return 0;
}