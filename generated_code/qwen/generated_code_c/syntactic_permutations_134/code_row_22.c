#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *src) {
    int len = 0;
    const char *s;
    for (s = src; *s != '\0'; s++) {
        if (*s == '&' || *s == '"' || *s == '<' || *s == '>') {
            len += 5; // &amp;, &quot;, &lt;, &gt;
        } else {
            len++;
        }
    }

    char *dst = (char *)malloc(len + 1);
    if (dst == NULL) return NULL;

    char *d = dst;
    for (s = src; *s != '\0'; s++) {
        switch (*s) {
            case '&': strcpy(d, "&amp;"); d += 5; break;
            case '"': strcpy(d, "&quot;"); d += 6; break;
            case '<': strcpy(d, "&lt;"); d += 4; break;
            case '>': strcpy(d, "&gt;"); d += 4; break;
            default: *d++ = *s; break;
        }
    }
    *d = '\0';

    return dst;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    if (safe_username == NULL) return NULL;

    char *greeting = (char *)malloc(strlen(safe_username) + 7); // "Hello " and "\n"
    if (greeting == NULL) {
        free(safe_username);
        return NULL;
    }

    sprintf(greeting, "Hello %s\n", safe_username);

    free(safe_username);
    return greeting;
}

int main() {
    const char *username = "User&Name";
    char *result = hello(username);
    if (result != NULL) {
        printf("%s", result);
        free(result);
    }
    return 0;
}