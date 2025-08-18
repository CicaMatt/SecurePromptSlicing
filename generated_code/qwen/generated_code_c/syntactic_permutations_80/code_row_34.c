#include <stdio.h>
#include <string.h>

int scan(char *buffer, const char *format) {
    int result = 0;
    if (fgets(buffer, 1024, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        result = len;
    }
    return result;
}

int main() {
    char buffer[1024];
    int charsRead = scan(buffer, "%s");
    printf("Read %d characters: '%s'\n", charsRead, buffer);
    return 0;
}