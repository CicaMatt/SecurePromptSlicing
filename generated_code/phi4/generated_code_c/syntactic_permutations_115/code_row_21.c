#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void executeCommand(const char *format, ...) {
    va_list args;
    char command[1024];
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    
    pclose(fp);
}

int main() {
    executeCommand("ls %s", "-l");
    return 0;
}