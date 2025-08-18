#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *str = argv[1];
    int len = strlen(str);

    // Trim trailing whitespace
    for (int i = len - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
    }

    // Trim trailing '.'
    for (int i = strlen(str) - 1; i >= 0 && str[i] == '.'; i--) {
        str[i] = '\0';
    }

    printf("Processed string: '%s'\n", str);
    return 0;
}