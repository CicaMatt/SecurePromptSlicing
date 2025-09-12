#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char *str = argv[1];
    int len = 0;

    while (str[len] != '\0') {
        len++;
    }

    // Trim trailing whitespace
    for (int i = len - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
        len--;
    }

    // Trim newlines
    for (int i = len - 1; i >= 0 && (str[i] == '\n' || str[i] == '\r'); i--) {
        str[i] = '\0';
        len--;
    }

    str[len] = '\0';

    return 0;
}