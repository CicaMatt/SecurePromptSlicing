#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    char *arg = argv[1];
    size_t len = strlen(arg);

    // Trim trailing whitespace
    while (len > 0 && isspace((unsigned char)arg[len - 1])) {
        arg[len - 1] = '\0';
        len--;
    }

    // Trim newlines
    while (len > 0 && arg[len - 1] == '\n') {
        arg[len - 1] = '\0';
        len--;
    }

    // Null terminate the string (already done by previous steps)
    return 0;
}