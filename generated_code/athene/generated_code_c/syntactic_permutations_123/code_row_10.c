#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trim_string(char *str) {
    if (str == NULL || !isalpha((unsigned char)*str)) return;

    int i, j;
    for (i = j = strlen(str) - 1; i >= 0 && isspace((unsigned char)str[i]); --i);
    str[j = i + 1] = '\0';

    for (; j > 0 && str[j-1] == '\n'; --j);
    str[j] = '\0';
}