#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char *str = argv[1];
    int length = 0;

    while (str[length] != '\0') {
        length++;
    }

    for (int i = length - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
        length--;
    }

    for (int i = length - 1; i >= 0; i--) {
        if (str[i] == '\n') {
            str[i] = '\0';
            length--;
        } else {
            break;
        }
    }

    str[length] = '\0';

    printf("Processed string: '%s'\n", str);

    return 0;
}