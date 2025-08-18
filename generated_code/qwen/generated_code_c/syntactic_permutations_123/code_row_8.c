#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[] = "Hello World!   \n\n";
    int i;

    // Trim trailing whitespace
    for (i = strlen(str) - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
    }

    // Trim newlines
    for (i = strlen(str) - 1; i >= 0 && (str[i] == '\n' || str[i] == '\r'); i--) {
        str[i] = '\0';
    }

    // Null terminate the string
    str[strlen(str)] = '\0';

    printf("Trimmed string: '%s'\n", str);
    return 0;
}