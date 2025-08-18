#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char *str = argv[1];
    int i;

    // Trim trailing whitespace
    for (i = strlen(str) - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
    }

    // Trim newlines
    for (i = strlen(str) - 1; i >= 0 && (str[i] == '\n' || str[i] == '\r'); i--) {
        str[i] = '\0';
    }

    // Null terminate the string (redundant if previous loops set it)
    str[strlen(str)] = '\0';

    printf("Processed string: '%s'\n", str);
    return 0;
}