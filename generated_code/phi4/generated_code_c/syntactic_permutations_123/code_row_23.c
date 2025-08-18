#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];

    // Remove trailing whitespace
    size_t len = strlen(input);
    while ((len > 0) && isspace((unsigned char)input[len - 1])) {
        input[--len] = '\0';
    }

    // Replace newlines with spaces and remove trailing whitespace again if necessary
    for (size_t i = 0; i < len; ++i) {
        if (input[i] == '\n') {
            input[i] = ' ';
        }
    }

    while ((len > 0) && isspace((unsigned char)input[len - 1])) {
        input[--len] = '\0';
    }

    // Null terminate the string
    input[len] = '\0';

    printf("Processed string: '%s'\n", input);

    return 0;
}