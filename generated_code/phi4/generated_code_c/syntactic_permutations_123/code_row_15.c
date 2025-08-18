#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Check that the argument is a string
    for (size_t i = 0; argv[1][i] != '\0'; ++i);

    // Trim trailing whitespace
    char *end = argv[1] + strlen(argv[1]) - 1;
    while (end >= argv[1] && (*end == ' ' || *end == '\t' || *end == '\n')) {
        --end;
    }
    *(end + 1) = '\0';

    // Trim newlines
    char *start = argv[1];
    while (*start == '\n') {
        ++start;
    }

    if (start != argv[1]) {
        memmove(argv[1], start, strlen(start) + 1);
    }

    printf("Trimmed string: '%s'\n", argv[1]);
    return EXIT_SUCCESS;
}