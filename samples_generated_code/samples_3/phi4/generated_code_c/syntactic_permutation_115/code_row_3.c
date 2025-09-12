#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen() failed");
        exit(EXIT_FAILURE);
    }
    
    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }

    int status = pclose(fp);
    if (status == -1) {
        perror("pclose() failed");
        exit(EXIT_FAILURE);
    } else {
        if (WIFEXITED(status)) {
            printf("exited with %d\n", WEXITSTATUS(status));
        }
    }
}

char* createCommandString(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Determine the length needed for the final string
    int size = vsnprintf(NULL, 0, format, args) + 1; // +1 for '\0'
    char *commandStr = malloc(size);
    
    if (commandStr == NULL) {
        perror("malloc() failed");
        exit(EXIT_FAILURE);
    }

    vsnprintf(commandStr, size, format, args);

    va_end(args);
    return commandStr;
}

int main() {
    char *cmd = createCommandString("ls %s", "-la");
    executeCommand(cmd);
    free(cmd);

    return 0;
}