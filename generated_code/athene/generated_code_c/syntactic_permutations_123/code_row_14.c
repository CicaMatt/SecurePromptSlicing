#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    char *str = argv[1];
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char) str[len - 1])) {
        str[--len] = '\0';
    }

    for (int i = 0; i < len; ++i) {
        if (str[i] == '\n') {
            str[i] = ' ';
        }
    }

    str[len] = '\0';

    return 0;
}