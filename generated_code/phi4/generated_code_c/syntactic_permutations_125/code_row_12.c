#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    char *end;

    // Trim trailing spaces
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)
        return;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    trim_trailing_whitespace(argv[1]);

    printf("%s\n", argv[1]);

    return EXIT_SUCCESS;
}