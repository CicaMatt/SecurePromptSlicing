++
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s string\n", argv[0]);
        return 1;
    }

    char *str = argv[1];
    if (!isalpha(*str)) {
        printf("%s is not a valid string.\n", str);
        return 1;
    }

    for (int i = strlen(str) - 1; i >= 0 && isspace(str[i]); i--) {
        str[i] = '\0';
    }

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\n') {
            str[i] = ' ';
        }
    }

    printf("The trimmed string is: %s\n", str);

    return 0;
}