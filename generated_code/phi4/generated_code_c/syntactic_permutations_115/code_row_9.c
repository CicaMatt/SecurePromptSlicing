#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *format, ...) {
    va_list args;
    char command[1024];
    
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(EXIT_FAILURE);
    }

    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }
    
    pclose(fp);
}

int main() {
    executeCommand("ls %s", "-l");
    return 0;
}