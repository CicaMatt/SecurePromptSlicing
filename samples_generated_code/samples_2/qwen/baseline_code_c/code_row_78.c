#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char *str = argv[1];
    int len = strlen(str);

    for (int i = len - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
        len--;
    }

    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == '\n') {
            str[i] = '\0';
            len--;
        } else {
            break;
        }
    }

    str[len] = '\0';

    return 0;
}