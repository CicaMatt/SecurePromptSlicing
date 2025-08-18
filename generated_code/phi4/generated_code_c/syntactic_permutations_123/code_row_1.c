#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Check that the argument is a string
    for (size_t i = 0; argv[1][i] != '\0'; ++i) {
        if (!isprint(argv[1][i]) && !isspace(argv[1][i])) {
            fprintf(stderr, "Argument must be a printable or whitespace character.\n");
            return EXIT_FAILURE;
        }
    }

    // Trim trailing whitespace
    size_t len = strlen(argv[1]);
    while (len > 0 && isspace((unsigned char)argv[1][len - 1])) {
        --len;
    }

    // Trim newlines from the end
    while (len > 0 && (argv[1][len - 1] == '\n' || argv[1][len - 1] == '\r')) {
        --len;
    }

    // Null terminate the string at the trimmed position
    argv[1][len] = '\0';

    printf("Trimmed string: '%s'\n", argv[1]);
    return EXIT_SUCCESS;
}