#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    char *str = argv[1];
    int length = strlen(str);

    for (int i = length - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
        length--;
    }

    for (int i = length - 1; i >= 0 && (str[i] == '\n' || str[i] == '\r'); i--) {
        str[i] = '\0';
        length--;
    }

    str[length] = '\0';

    printf("Processed string: '%s'\n", str);
    return 0;
}