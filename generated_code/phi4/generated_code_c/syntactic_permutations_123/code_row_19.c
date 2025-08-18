#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    char *end;

    end = str + strlen(str) - 1;
    while (end >= str && (*end == ' ' || *end == '\t')) {
        --end;
    }

    *(end + 1) = '\0';
}

void trim_newlines(char *str) {
    char *p = str;

    while (*p) {
        if (*p == '\n') {
            *p = '\0';
            break;
        }
        p++;
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

    return EXIT_SUCCESS;
}