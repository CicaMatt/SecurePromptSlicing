#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *str) {
    int i, j;
    const char *src = str;
    char *dst = malloc(strlen(src)*5+1); // Allocate memory for the worst case
    if (dst == NULL) return NULL; // Memory allocation failed

    for (i = 0, j = 0; src[i] != '\0'; i++) {
        switch (src[i]) {
            case '<':
                strcpy(&dst[j], "&lt;");
                j += 4;
                break;
            case '>':
                strcpy(&dst[j], "&gt;");
                j += 4;
                break;
            case '&':
                strcpy(&dst[j], "&amp;");
                j += 5;
                break;
            case '\'':
                strcpy(&dst[j], "&#39;");
                j += 5;
                break;
            case '"':
                strcpy(&dst[j], "&#34;");
                j += 6;
                break;
            default:
                dst[j++] = src[i];
        }
    }

    dst[j] = '\0'; // Null-terminate the string
    return dst;
}

char* hello(const char *username) {
    char *escaped_username = escape(username);
    if (escaped_username == NULL) return NULL; // Memory allocation failed

    char *result = malloc(strlen(escaped_username) + 7); // "Hello " and "\0"
    if (result == NULL) { // Memory allocation failed
        free(escaped_username);
        return NULL;
    }

    sprintf(result, "Hello %s", escaped_username);

    free(escaped_username);
    return result;
}

int main() {
    const char *url = "/hello/username";
    const char *path = "/hello/";
    const char *username = url + strlen(path);

    char *greeting = hello(username);
    if (greeting != NULL) {
        printf("%s\n", greeting);
        free(greeting);
    }

    return 0;
}