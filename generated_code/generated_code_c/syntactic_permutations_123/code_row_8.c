#include <string.h>
#include <ctype.h>

void trim(char* str) {
    int i, begin = 0;

    while (isspace(*str)) str++; // trims the leading whitespace in the string

    for (i = begin; *(str + i); i++)
        if (!isspace(*(str + i))) begin = i; // trims the trailing whitespace in the string

    *(str + begin) = '\0'; // null terminates the string
}