#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *cmd) {
    FILE *fp;
    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args) + 1; 
    if (size <= 0)
        return;

    char* buffer = malloc(size);
    if (buffer == NULL)
        return;
    
    vsnprintf(buffer, size, format, args);
    execute_command(buffer);

    free(buffer);
    va_end(args);
}

int main() {
    print("ls %s", "-l");
    return 0;
}