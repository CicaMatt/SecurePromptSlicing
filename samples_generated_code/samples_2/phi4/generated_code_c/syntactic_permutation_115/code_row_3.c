#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }
    
    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }

    pclose(fp);
}

void printAndExecute(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the required buffer size
    int needed = vsnprintf(NULL, 0, format, args);
    if (needed <= 0) {
        perror("vsnprintf failed");
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(needed + 1);
    if (!buffer) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    
    vsnprintf(buffer, needed + 1, format, args);

    executeCommand(buffer);

    free(buffer);
    va_end(args);
}

int main() {
    printAndExecute("ls %s", NULL);
    return 0;
}