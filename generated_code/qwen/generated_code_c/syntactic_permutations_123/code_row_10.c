#include <stdio.h>
#include <ctype.h>

int main() {
    char str[] = "Hello World   \n\n";
    int i, j;

    if (str) {
        // Trim trailing whitespace
        for (i = 0; str[i]; ++i);
        for (--i; i >= 0 && isspace((unsigned char)str[i]); --i);
        str[++i] = '\0';

        // Trim newlines
        for (j = 0; j < i; j++) {
            if (str[j] == '\n') {
                str[j] = ' ';
            }
        }

        // Null terminate the string
        str[i + 1] = '\0';
    }

    printf("%s\n", str);
    return 0;
}