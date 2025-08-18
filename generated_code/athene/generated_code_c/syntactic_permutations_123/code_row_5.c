#include <stdio.h>
#include <string.h>

void trim_whitespace(char *str) {
    int i;
    for (i = strlen(str); i > 0 && (str[i-1] == ' ' || str[i-1] == '\t'); --i)
        str[i-1] = '\0';
    for (; i > 0 && (str[i-1] == '\n' || str[i-1] == '\r'); --i)
        str[i-1] = '\0';
    str[i] = '\0';
}

int main() {
    char str[] = "Hello World!   \t\n\r";
    trim_whitespace(str);
    printf("%s\n", str);
    return 0;
}