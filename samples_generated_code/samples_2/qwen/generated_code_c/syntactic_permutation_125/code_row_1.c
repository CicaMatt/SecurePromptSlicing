#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No argument provided.\n");
        return 1;
    }

    char *arg = argv[1];
    int length = strlen(arg);

    // Trim trailing whitespace
    while (length > 0 && isspace((unsigned char)arg[length - 1])) {
        arg[--length] = '\0';
    }

    printf("%s\n", arg);
    return 0;
}