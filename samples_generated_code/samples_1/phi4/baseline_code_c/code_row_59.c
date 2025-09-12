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
    int len = strlen(input);

    // Trim trailing whitespace
    while (len > 0 && isspace((unsigned char)input[len - 1])) {
        --len;
    }
    
    // Trim newlines
    for (int i = 0; i < len; ++i) {
        if (input[i] == '\n' || input[i] == '\r') {
            memmove(input + i, input + i + 1, len - i);
            --len;
            --i; // recheck the same position
        }
    }

    input[len] = '\0'; // Null terminate the string

    printf("Trimmed string: '%s'\n", input);

    return EXIT_SUCCESS;
}