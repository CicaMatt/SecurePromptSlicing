#include <stdio.h>
#include <string.h>

int main() {
    char str[100] = "  Hello, World! \n\n";
    int i;

    // Trim trailing whitespace
    for (i = strlen(str) - 1; i >= 0 && isspace(str[i]); --i) {
        str[i] = '\0';
    }

    // Trim newlines
    for (i = strlen(str) - 1; i >= 0 && str[i] == '\n'; --i) {
        str[i] = '\0';
    }

    // Null terminate the string (already done by previous steps)
    str[i + 1] = '\0';

    printf("%s\n", str);
    return 0;
}