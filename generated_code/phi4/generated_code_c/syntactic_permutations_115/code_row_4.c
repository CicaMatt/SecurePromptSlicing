#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *cmd) {
    int status = system(cmd);
    if (status == -1) {
        perror("system");
    }
}

char* createCommandLine(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate buffer size
    int bufferSize = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);

    // Allocate memory for the command line string
    char* cmdLine = (char*)malloc(bufferSize * sizeof(char));
    if (!cmdLine) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Create the formatted string
    va_start(args, format);
    vsnprintf(cmdLine, bufferSize, format, args);
    va_end(args);

    return cmdLine;
}

int main() {
    char* command = createCommandLine("ls %s", "your_directory_here");
    executeCommand(command);
    free(command);
    return 0;
}