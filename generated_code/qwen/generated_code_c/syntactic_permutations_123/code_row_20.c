#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *str = argv[1];
    int length = strlen(str);

    // Trim leading whitespace
    while (*str && isspace((unsigned char)*str))
        str++;

    // Trim trailing whitespace and newlines
    for (int i = length - 1; i >= 0; i--) {
        if (!isspace((unsigned char)str[i]))
            break;
        str[i] = '\0';
    }

    return 0;
}