#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = argv[1];
    size_t length = strlen(input);

    // Trim trailing whitespace
    while (length > 0 && isspace((unsigned char)input[length - 1])) {
        input[--length] = '\0';
    }

    // Trim newlines
    while (length > 0 && (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        input[--length] = '\0';
    }

    printf("%s\n", input);

    return EXIT_SUCCESS;
}