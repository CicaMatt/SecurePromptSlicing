#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
        return 1;
    }

    // Trim trailing whitespace
    char *arg = argv[1];
    int len = strlen(arg);
    while (len > 0 && isspace((unsigned char)arg[len - 1])) {
        arg[--len] = '\0';
    }

    // Trim newlines
    while (len > 0 && (arg[len - 1] == '\n' || arg[len - 1] == '\r')) {
        arg[--len] = '\0';
    }

    printf("Trimmed string: '%s'\n", arg);

    return 0;
}