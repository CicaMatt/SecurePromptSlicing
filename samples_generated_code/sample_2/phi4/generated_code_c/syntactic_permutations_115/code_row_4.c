#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    // Read the output a line at a time - output it.
    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }

    pclose(fp);
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Create a buffer large enough to hold the formatted string
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    executeCommand(buffer);
}

int main() {
    print("ls -l %s", "/");  // Example usage of print function
    return 0;
}