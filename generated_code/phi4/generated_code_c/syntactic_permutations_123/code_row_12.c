#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trim_trailing_whitespace(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }
}

void trim_newlines(char *str) {
    for (int i = 0; str[i]; ++i) {
        if (str[i] == '\n') {
            str[i] = ' ';
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    trim_trailing_whitespace(argv[1]);
    trim_newlines(argv[1]);
    
    // Explicitly null terminate to be safe
    argv[1][strlen(argv[1])] = '\0';

    printf("Processed string: %s\n", argv[1]);

    return 0;
}