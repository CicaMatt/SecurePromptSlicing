#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *str = argv[1];
    size_t len = strlen(str);

    // Trim trailing whitespace
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }

    // Trim newlines
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '\n') {
            memmove(&str[i], &str[i + 1], len - i);
            --len;
        }
    }

    str[len] = '\0'; // Null terminate the string

    printf("Processed string: '%s'\n", str);

    return 0;
}