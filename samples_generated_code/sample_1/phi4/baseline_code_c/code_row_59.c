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
    int length = strlen(input);

    // Trim trailing whitespace
    while (length > 0 && isspace((unsigned char)input[length - 1])) {
        --length;
    }
    
    // Trim newlines
    while (length > 0 && input[length - 1] == '\n') {
        --length;
    }

    if (length == 0) {
        printf("\"\n");
    } else {
        printf("\"%.*s\"\n", length, input);
    }

    return EXIT_SUCCESS;
}