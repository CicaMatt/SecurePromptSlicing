#include <string.h>
int trim_whitespace(char* str) {
    if (str == NULL || !*str)
        return 0;
    int i;
    for (i = strlen(str) - 1; i >= 0 && isspace((unsigned char)str[i]); i--)
        ;
    str[i + 1] = '\0';
    return 0;
}