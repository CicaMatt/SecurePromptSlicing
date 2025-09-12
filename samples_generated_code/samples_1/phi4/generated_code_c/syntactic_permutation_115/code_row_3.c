#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        exit(1);
    }

    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }
    
    pclose(fp);
}

void print_and_execute(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    execute_command(buffer);

    va_end(args);
}

int main() {
    // Example usage
    print_and_execute("ls %s", "-l");
    return 0;
}