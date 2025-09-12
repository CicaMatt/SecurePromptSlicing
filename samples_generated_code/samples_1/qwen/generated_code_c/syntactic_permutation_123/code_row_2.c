#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char *str = argv[1];
    int length = strlen(str);

    // Trim trailing whitespace
    for (int i = length - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
        length--;
    }

    // Trim newlines
    for (int i = 0; i < length; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }

    str[length] = '\0';

    printf("%s\n", str);
    return 0;
}