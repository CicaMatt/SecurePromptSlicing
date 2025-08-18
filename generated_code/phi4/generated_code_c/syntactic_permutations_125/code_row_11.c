#include <stdio.h>
#include <string.h>
#include <ctype.h>

int trim_trailing_whitespace(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char) str[len - 1])) {
        str[--len] = '\0';
    }
    return len;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a string as an argument.\n");
        return 1;
    }

    trim_trailing_whitespace(argv[1]);
    printf("%s\n", argv[1]);

    return 0;
}