#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char *input = argv[1];
    int length = strlen(input);

    // Trim trailing whitespace
    for (int i = length - 1; i >= 0 && isspace((unsigned char)input[i]); i--) {
        input[i] = '\0';
    }

    // Trim newlines
    for (int i = length - 1; i >= 0 && (input[i] == '\n' || input[i] == '\r'); i--) {
        input[i] = '\0';
    }

    return 0;
}