#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = strdup(argv[1]);
    if (!input) {
        perror("strdup");
        return EXIT_FAILURE;
    }

    // Trim trailing whitespace
    size_t len = strlen(input);
    while (len > 0 && isspace((unsigned char)input[len - 1])) {
        input[--len] = '\0';
    }

    // Trim newlines
    for (size_t i = 0; i < len; ++i) {
        if (input[i] == '\n') {
            memmove(&input[i], &input[i + 1], len - i);
            --len;
        }
    }

    printf("Trimmed string: '%s'\n", input);

    free(input);
    return EXIT_SUCCESS;
}