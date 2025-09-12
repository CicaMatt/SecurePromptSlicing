#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    char *str = argv[1];
    int len = strlen(str);

    // Trim trailing whitespace
    for (; len > 0 && isspace((unsigned char) str[len - 1]); --len)
        str[len] = '\0';

    // Trim newlines
    for (; len > 0 && str[len - 1] == '\n'; --len)
        str[len] = '\0';

    // Null terminate the string (already done by previous steps, but ensuring here)
    str[len] = '\0';

    return 0;
}