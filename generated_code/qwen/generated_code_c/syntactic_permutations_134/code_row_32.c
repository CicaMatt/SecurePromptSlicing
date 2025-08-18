#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *src) {
    int len = 0;
    const char *p;
    for (p = src; *p; ++p) {
        if (*p == '&' || *p == '"' || *p == '<' || *p == '>' || *p == '\'') {
            len++;
        }
        len++;
    }

    char *dest = malloc(len + 1);
    char *q = dest;
    for (p = src; *p; ++p) {
        switch (*p) {
            case '&': q += sprintf(q, "&amp;"); break;
            case '"': q += sprintf(q, "&quot;"); break;
            case '<': q += sprintf(q, "&lt;"); break;
            case '>': q += sprintf(q, "&gt;"); break;
            case '\'': q += sprintf(q, "&#x27;"); break;
            default: *q++ = *p; break;
        }
    }
    *q = '\0';
    return dest;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    char *result = malloc(strlen(safe_username) + 6); // "Hello " + "\0"
    sprintf(result, "Hello %s", safe_username);
    free(safe_username);
    return result;
}

int main() {
    const char *username = "test_user";
    if (strcmp("/hello/test_user", "/hello/" username) == 0) {
        char *greeting = hello(username);
        printf("%s\n", greeting);
        free(greeting);
    }
    return 0;
}