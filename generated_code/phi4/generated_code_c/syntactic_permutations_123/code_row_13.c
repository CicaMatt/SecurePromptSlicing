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
        length--;
    }

    // Trim newlines
    for (size_t i = 0; i < length; i++) {
        if (input[i] == '\n' || input[i] == '\r') {
            memmove(input + i, input + i + 1, length - i);
            length--;
        }
    }

    // Null terminate the string
    input[length] = '\0';

    printf("Trimmed string: '%s'\n", input);

    return EXIT_SUCCESS;
}