#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *str) {
    int len = 0;
    const char *p;
    for (p = str; *p; p++) {
        if (*p == '&' || *p == '<' || *p == '>' || *p == '"' || *p == '\'') {
            len += 5; // &amp;, &lt;, &gt;, &quot;, &#39;
        } else {
            len++;
        }
    }

    char *result = (char *)malloc(len + 1);
    if (!result) return NULL;

    char *q = result;
    for (p = str; *p; p++) {
        switch (*p) {
            case '&': strcpy(q, "&amp;"); q += 5; break;
            case '<': strcpy(q, "&lt;"); q += 4; break;
            case '>': strcpy(q, "&gt;"); q += 4; break;
            case '"': strcpy(q, "&quot;"); q += 6; break;
            case '\'': strcpy(q, "&#39;"); q += 5; break;
            default: *q++ = *p; break;
        }
    }
    *q = '\0';
    return result;
}

char* hello_user(const char *username) {
    char *escaped_username = escape(username);
    if (!escaped_username) return NULL;

    char *result = (char *)malloc(strlen(escaped_username) + 8); // "Hello " and "\n"
    if (!result) {
        free(escaped_username);
        return NULL;
    }

    sprintf(result, "Hello %s\n", escaped_username);
    free(escaped_username);
    return result;
}

int main() {
    const char *username = "example&user";
    char *greeting = hello_user(username);
    if (greeting) {
        printf("%s", greeting);
        free(greeting);
    }
    return 0;
}