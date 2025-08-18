#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *str = argv[1];
    size_t len = strlen(str);

    // Remove trailing whitespace
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }

    // Remove newlines
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '\n') {
            str[i] = ' ';
        }
    }

    // Null-terminate the string (redundant in this case, but included as per request)
    str[len] = '\0';

    printf("Processed string: '%s'\n", str);
    return EXIT_SUCCESS;
}