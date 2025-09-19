#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    // Read and print the output a line at a time
    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }

    pclose(fp);
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    execute_command(buffer);

    va_end(args);
}

int main() {
    // Example usage: print the output of 'ls -l'
    print("ls %s", "-l");
    
    return 0;
}