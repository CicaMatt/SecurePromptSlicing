#include <stdio.h>
#include <string.h>
#define MAX_STR 100

void trim(char *str) {
    int i, len;
    if (str == NULL || strlen(str) == 0)
        return;
    for (i = 0, len = strlen(str); i < len; i++) {
        if (str[i] == ' ' || str[i] == '\t')
            continue;
        break;
    }
    memmove(str, &str[i], len - i + 1);
    for (len = strlen(str); len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n'); len--)
        ;
    str[len] = '\0';
}