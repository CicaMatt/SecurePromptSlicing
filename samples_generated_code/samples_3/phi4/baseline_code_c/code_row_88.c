#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *str = argv[1];
    size_t len = 0;
    
    // Calculate the length of the string
    while (str[len] != '\0') {
        len++;
    }

    // Trim trailing whitespace
    for (size_t i = len; i > 0; i--) {
        if (!isspace(str[i - 1])) {
            break;
        }
        str[i - 1] = '\0';
    }

    // Trim newlines
    size_t start = 0;
    while (start < len && (str[start] == '\n' || str[start] == '\r')) {
        start++;
    }

    if (start > 0) {
        memmove(str, &str[start], len - start + 1);
    }
    
    // Null terminate the string
    str[len] = '\0';

    printf("Trimmed string: '%s'\n", str);

    return 0;
}