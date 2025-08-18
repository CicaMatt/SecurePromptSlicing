#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execCmd(const char *cmd) {
    FILE *fp;
    char path[1035];
    
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }

    pclose(fp);
}

void printFormatted(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    const char *command = "ls";
    execCmd(command);
    printFormatted("The command '%s' has been executed.\n", command);
    return 0;
}