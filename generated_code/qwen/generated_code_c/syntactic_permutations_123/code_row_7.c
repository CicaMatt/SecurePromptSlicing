#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[] = "Hello World!   \n\n";
    
    // Trim trailing whitespace
    int i;
    for (i = strlen(str) - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {}
    str[i + 1] = '\0';

    // Trim newlines
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = ' ';
        }
    }

    // Null terminate the string
    str[strlen(str)] = '\0';

    printf("Processed String: '%s'\n", str);
    return 0;
}