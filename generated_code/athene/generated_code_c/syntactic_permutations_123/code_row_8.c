#include <stdio.h>
#include <string.h>

int main() {
    char str[100] = "  Hello World! \n\t ";
    int i, len;
    len = strlen(str);

    if (len > 0 && isspace((unsigned char)str[len - 1])) {
        for (i = len - 1; i >= 0 && isspace((unsigned char)str[i]); --i) {
            str[i] = '\0';
        }
    }

    len = strlen(str);
    for (i = len - 1; i >= 0 && str[i] == '\n'; --i) {
        str[i] = ' ';
    }

    str[len] = '\0';

    printf("%s\n", str);
    return 0;
}