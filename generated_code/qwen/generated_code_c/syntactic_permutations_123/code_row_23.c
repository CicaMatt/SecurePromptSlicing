#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = argv[1];
    size_t len = strlen(input);

    // Remove trailing whitespace
    while (len > 0 && isspace((unsigned char)input[len - 1])) {
        input[--len] = '\0';
    }

    // Remove newlines
    for (size_t i = 0; i < len; ++i) {
        if (input[i] == '\n') {
            input[i] = ' ';
        }
    }

    // Null-terminate the string (already done by removing trailing whitespace)
    input[len] = '\0';

    printf("Processed string: '%s'\n", input);
    return EXIT_SUCCESS;
}