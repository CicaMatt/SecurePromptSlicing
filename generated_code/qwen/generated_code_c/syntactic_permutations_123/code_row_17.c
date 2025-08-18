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
    int len = strlen(str);

    // Trim trailing whitespace
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }

    // Trim newlines
    for (int i = 0; i < len; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }

    // Null terminate the string (already done in previous steps, but just to be safe)
    str[len] = '\0';

    printf("Processed string: '%s'\n", str);

    return 0;
}