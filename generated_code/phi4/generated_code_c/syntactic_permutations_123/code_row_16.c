#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }
}

void trim_newlines(char *str) {
    for (int i = 0; str[i]; ++i) {
        if (str[i] == '\n') {
            str[i] = ' ';
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    trim_trailing_whitespace(argv[1]);
    trim_newlines(argv[1]);

    printf("Processed string: '%s'\n", argv[1]);

    // Null terminate manually (redundant because strings are null-terminated in C)
    argv[1][strlen(argv[1])] = '\0';

    return EXIT_SUCCESS;
}