#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
        return 1;
    }

    // Check that the argument is a string
    for (size_t i = 0; i < strlen(argv[1]); ++i) {
        if (!isprint((unsigned char)argv[1][i]) && !isspace((unsigned char)argv[1][i])) {
            fprintf(stderr, "Argument must be a printable string.\n");
            return 1;
        }
    }

    // Trim trailing whitespace and newlines
    size_t len = strlen(argv[1]);
    while (len > 0 && isspace((unsigned char)argv[1][len - 1])) {
        --len;
    }
    
    argv[1][len] = '\0';

    printf("Processed string: %s\n", argv[1]);

    return 0;
}