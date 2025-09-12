#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *str = argv[1];
    size_t len = strlen(str);

    // Trim trailing whitespace
    for (; len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'); --len) {
        str[len - 1] = '\0';
    }

    // Trim newlines
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }

    printf("Processed string: '%s'\n", str);
    return 0;
}