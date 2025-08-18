#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    
    pclose(fp);
}

void printCommand(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char command[1024] = "";
    vsnprintf(command, sizeof(command), format, args);

    va_end(args);

    executeCommand(command);
}

int main() {
    printCommand("ls %s", "-l");
    return 0;
}