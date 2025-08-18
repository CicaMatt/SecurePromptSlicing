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

    // Trim trailing whitespace
    for (size_t i = len; i > 0 && isspace((unsigned char)input[i - 1]); --i);
    input[i] = '\0';

    // Trim newlines
    for (size_t j = 0; j < len && (input[j] == '\n' || input[j] == '\r'); ++j);
    memmove(input, &input[j], strlen(&input[j]) + 1);

    printf("%s\n", input);
    return EXIT_SUCCESS;
}