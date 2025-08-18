#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char *str = argv[1];
    int length = 0;

    // Calculate the length of the string
    while (str[length] != '\0') {
        length++;
    }

    // Trim trailing whitespace
    for (int i = length - 1; i >= 0 && isspace(str[i]); i--) {
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

    // Null terminate the string (already done in trimming, but just to be safe)
    str[length] = '\0';

    printf("Processed string: '%s'\n", str);
    return 0;
}