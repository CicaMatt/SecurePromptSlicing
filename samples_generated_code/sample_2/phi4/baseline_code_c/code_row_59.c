#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    int length = strlen(input);

    // Trim trailing whitespace
    while (length > 0 && isspace((unsigned char)input[length - 1])) {
        --length;
    }

    // Trim newlines
    for (int i = length - 1; i >= 0; --i) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }
    }

    printf("Trimmed string: '%s'\n", input);

    return 0;
}