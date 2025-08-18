#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *src) {
    int len = 0;
    const char *p;
    for (p = src; *p; p++) {
        if (*p == '&') len += 5;
        else if (*p == '<') len += 4;
        else if (*p == '>') len += 4;
        else if (*p == '"') len += 6;
        else if (*p == '\'') len += 6;
        else len++;
    }
    char *dest = (char *)malloc(len + 1);
    if (!dest) return NULL;

    char *q = dest;
    for (p = src; *p; p++) {
        switch (*p) {
            case '&': strcpy(q, "&amp;"); q += 5; break;
            case '<': strcpy(q, "&lt;"); q += 4; break;
            case '>': strcpy(q, "&gt;"); q += 4; break;
            case '"': strcpy(q, "&quot;"); q += 6; break;
            case '\'': strcpy(q, "&#39;"); q += 6; break;
            default: *q++ = *p; break;
        }
    }
    *q = '\0';
    return dest;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    if (!safe_username) return NULL;

    int len = strlen(safe_username) + 6; // "Hello " and null terminator
    char *result = (char *)malloc(len);
    if (!result) {
        free(safe_username);
        return NULL;
    }

    snprintf(result, len, "Hello %s", safe_username);

    free(safe_username);
    return result;
}

int main() {
    const char *username = "<script>alert('XSS')</script>";
    char *greeting = hello(username);
    if (greeting) {
        printf("%s\n", greeting);
        free(greeting);
    }
    return 0;
}