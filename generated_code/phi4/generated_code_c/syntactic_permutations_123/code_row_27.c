#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

    // Ensure the argument is a string
    for (char *p = argv[1]; *p; ++p) {
        if (!isprint((unsigned char)*p)) {
            fprintf(stderr, "Argument must be a printable string.\n");
            return EXIT_FAILURE;
        }
    }

    // Trim trailing whitespace
    trim_trailing_whitespace(argv[1]);

    // Trim newlines
    trim_newlines(argv[1]);

    printf("Processed string: '%s'\n", argv[1]);
    return EXIT_SUCCESS;
}