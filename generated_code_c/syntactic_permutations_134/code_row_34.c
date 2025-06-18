#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char* str) {
    const char* special_chars = "<>&\"";
    const char* replacements = "lt;gt;&amp;quot;";

    int len = strlen(str);
    char* escaped = malloc((len * 2 + 1) * sizeof(char));
    if (!escaped) {
        return NULL;
    }

    int i, j;
    for (i = 0, j = 0; i < len; ++i) {
        char c = str[i];
        int k;
        for (k = 0; special_chars[k] != '\0'; ++k) {
            if (c == special_chars[k]) {
                escaped[j++] = '&';
                while (replacements[k] != ';') {
                    escaped[j++] = replacements[k++];
                }
                escaped[j++] = ';';
                break;
            }
        }
        if (special_chars[k] == '\0') {
            escaped[j++] = c;
        }
    }
    escaped[j] = '\0';

    return escaped;
}

char* hello(const char* username) {
    const char* message = "Hello, %s!";
    int len1 = strlen(message);
    int len2 = strlen(username);
    char* result = malloc((len1 + len2 + 1) * sizeof(char));
    if (!result) {
        return NULL;
    }

    sprintf(result, message, username);
    return result;
}