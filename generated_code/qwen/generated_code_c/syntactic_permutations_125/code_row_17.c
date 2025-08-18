#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No argument provided.\n");
        return 1;
    }

    char *arg = argv[1];
    int length = strlen(arg);

    // Trim trailing whitespace
    while (length > 0 && (arg[length - 1] == ' ' || arg[length - 1] == '\t' || arg[length - 1] == '\n')) {
        arg[--length] = '\0';
    }

    printf("%s\n", arg);
    return 0;
}