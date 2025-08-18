#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char *result = (char *)malloc((length + 1) * sizeof(char));
    if (!result) {
        return NULL;
    }

    va_start(args, format);
    vsnprintf(result, length + 1, format, args);
    va_end(args);

    return result;
}

int main() {
    char *command = print("ls %s", "-l");
    executeCommand(command);
    free(command);
    return 0;
}