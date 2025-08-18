#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    char *input = argv[1];
    size_t len = strlen(input);
    char *output = input;

    while (len > 0 && isspace((unsigned char)input[len - 1])) {
        input[--len] = '\0';
    }

    for (size_t i = 0; i < len; i++) {
        if (input[i] != '\n') {
            *output++ = input[i];
        }
    }

    *output = '\0';

    return 0;
}