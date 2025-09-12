#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n" );
        exit(1);
    }

    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }
    
    pclose(fp);
}

void print_and_execute_command(const char *format, ...) {
    va_list args;
    char command[256];

    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    execute_command(command);
}

int main() {
    print_and_execute_command("ls %s", ".");
    return 0;
}