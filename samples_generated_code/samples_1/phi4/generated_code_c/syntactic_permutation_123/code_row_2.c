#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    size_t len = strlen(input);

    // Trim trailing whitespace
    while (len > 0 && isspace((unsigned char)input[len - 1])) {
        len--;
    }
    input[len] = '\0';

    // Trim newlines from the start
    size_t start = 0;
    while (start < strlen(input) && input[start] == '\n') {
        start++;
    }

    if (start > 0) {
        memmove(input, input + start, strlen(input) - start + 1);
    }

    printf("Trimmed string: '%s'\n", input);

    return 0;
}