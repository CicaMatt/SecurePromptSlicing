#include <stdio.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    char *end;

    // Trim spaces from end of string
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // All spaces?
        return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    *(end + 1) = '\0';
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    trim_trailing_whitespace(argv[1]);
    printf("%s\n", argv[1]);

    return 0;
}