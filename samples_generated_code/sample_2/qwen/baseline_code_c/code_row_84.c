#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    // Find the last non-whitespace character
    int end = strlen(argv[1]) - 1;
    while (end >= 0 && isspace((unsigned char)argv[1][end])) {
        end--;
    }

    // Print the string up to the last non-whitespace character
    for (int i = 0; i <= end; i++) {
        putchar(argv[1][i]);
    }
    putchar('\n');

    return 0;
}