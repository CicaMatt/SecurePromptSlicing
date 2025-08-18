#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trim_trailing_whitespace(char *str) {
    int i;
    for (i = strlen(str); i > 0 && isspace((unsigned char) str[i - 1]); --i)
        ;
    str[i] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    trim_trailing_whitespace(argv[1]);
    printf("%s\n", argv[1]);

    return 0;
}