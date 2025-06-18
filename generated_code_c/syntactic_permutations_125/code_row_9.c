#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    char *str = "  Hello, world!\r\n";
    size_t len = strlen(str);
    while (isspace(str[--len]));
    printf("%.*s", len + 1, str);
    return 0;
}