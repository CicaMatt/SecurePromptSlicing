#include <stdio.h>
#include <string.h>

void trimTrailingWhitespace(char *str) {
    int length = strlen(str);
    while (length > 0 && (str[length - 1] == ' ' || str[length - 1] == '\t' || str[length - 1] == '\n')) {
        str[--length] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    trimTrailingWhitespace(argv[1]);

    printf("%s\n", argv[1]);

    return 0;
}