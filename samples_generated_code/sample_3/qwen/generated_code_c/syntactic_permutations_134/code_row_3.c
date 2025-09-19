#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    const char *p;
    char *q;
    int len = 0;
    for (p = str; *p != '\0'; p++) {
        if (*p == '&' || *p == '<' || *p == '>' || *p == '"' || *p == '\'') len++;
    }
    q = malloc(strlen(str) + len + 1);
    if (!q) return NULL;
    for (p = str, q = q; *p != '\0'; p++) {
        switch (*p) {
            case '&': *q++ = '&'; *q++ = 'a'; *q++ = 'm'; *q++ = 'p'; *q++ = ';'; break;
            case '<': *q++ = '&'; *q++ = 'l'; *q++ = 't'; *q++ = ';'; break;
            case '>': *q++ = '&'; *q++ = 'g'; *q++ = 't'; *q++ = ';'; break;
            case '"': *q++ = '&'; *q++ = 'q'; *q++ = 'u'; *q++ = 'o'; *q++ = 't'; *q++ = ';'; break;
            case '\'': *q++ = '&'; *q++ = '#'; *q++ = '3'; *q++ = '9'; *q++ = ';'; break;
            default: *q++ = *p; break;
        }
    }
    *q = '\0';
    return q - strlen(str) - len == str ? NULL : q - strlen(str) - len;
}

char* hello_function(const char *username) {
    char *escaped_username = escape(username);
    if (!escaped_username) return NULL;
    char *result = malloc(strlen(escaped_username) + 7); // "Hello " + escaped_username + '\0'
    if (!result) {
        free(escaped_username);
        return NULL;
    }
    sprintf(result, "Hello %s", escaped_username);
    free(escaped_username);
    return result;
}

int main() {
    const char *username = "user&name";
    char *greeting = hello_function(username);
    if (greeting) {
        printf("%s\n", greeting);
        free(greeting);
    }
    return 0;
}