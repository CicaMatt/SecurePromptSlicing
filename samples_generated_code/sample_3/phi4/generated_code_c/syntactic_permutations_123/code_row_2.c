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

    // Trim newlines from the beginning
    while (*input == '\n' || *input == '\r') {
        memmove(input, input + 1, length);
        --length;
    }

    printf("%s\n", input);

    return EXIT_SUCCESS;
}