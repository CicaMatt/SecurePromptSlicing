#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_string>\n", argv[0]);
        return 1;
    }

    // Trim trailing whitespace
    size_t len = strlen(argv[1]);
    while (len > 0 && isspace((unsigned char)argv[1][len - 1])) {
        --len;
    }
    argv[1][len] = '\0';

    // Trim newlines
    if (len > 0 && (argv[1][len - 1] == '\n' || argv[1][len - 1] == '\r')) {
        while (len > 0 && (argv[1][len - 1] == '\n' || argv[1][len - 1] == '\r')) {
            --len;
        }
    }

    // Null-terminate the string
    argv[1][len] = '\0';

    printf("Trimmed input: %s\n", argv[1]);
    return 0;
}