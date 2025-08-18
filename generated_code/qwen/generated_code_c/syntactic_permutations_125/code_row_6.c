#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <argument>\n", argv[0]);
        return 1;
    }

    char *arg = argv[1];
    int len = strlen(arg);

    // Trim trailing whitespace
    while (len > 0 && (arg[len - 1] == ' ' || arg[len - 1] == '\t' || arg[len - 1] == '\n')) {
        arg[--len] = '\0';
    }

    printf("Trimmed argument: '%s'\n", arg);
    return 0;
}