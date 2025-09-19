#include <stdio.h>
#include <string.h>

char* trim_trailing_whitespace(char *str) {
    char *end;

    // Trim leading space
    while (*str == ' ') str++;

    if (*str == 0) return str; // All spaces?

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;

    // Write new null terminator character
    *(end + 1) = '\0';

    return str;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *trimmed_string = trim_trailing_whitespace(argv[1]);
    printf("%s\n", trimmed_string);

    return 0;
}