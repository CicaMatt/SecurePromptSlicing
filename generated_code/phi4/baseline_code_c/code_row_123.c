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
    size_t length = strlen(input);

    // Trim trailing whitespace
    for (size_t i = length; i > 0; i--) {
        if (!isspace((unsigned char) input[i - 1])) break;
        input[i - 1] = '\0';
    }

    // Trim newlines
    size_t start_len = strlen(input);
    for (size_t i = 0; i < start_len; i++) {
        if (input[i] == '\n') {
            memmove(&input[i], &input[i + 1], strlen(&input[i]) + 1);
            --start_len;
            i--; // Recheck the current position as it's now occupied by a new character
        }
    }

    printf("Trimmed string: '%s'\n", input);

    return EXIT_SUCCESS;
}