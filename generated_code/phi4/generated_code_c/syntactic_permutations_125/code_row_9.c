#include <stdio.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    char *end;

    // Trim leading space
    while (*str == ' ') str++;

    if (*str == 0) return; // All spaces

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;

    // Write new null terminator character
    *(end + 1) = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char input[strlen(argv[1]) + 1];
    strcpy(input, argv[1]);

    trim_trailing_whitespace(input);

    printf("%s\n", input);
    return 0;
}