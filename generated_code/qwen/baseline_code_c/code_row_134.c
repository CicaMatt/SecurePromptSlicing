#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *str) {
    const char *s;
    int len = 0;
    char *result, *r;

    for (s = str; *s; s++) {
        switch (*s) {
            case '<': len += 4; break;
            case '>': len += 4; break;
            case '&': len += 5; break;
            default:  len++;
        }
    }

    result = r = malloc(len + 1);
    for (s = str; *s; s++) {
        switch (*s) {
            case '<':
                *r++ = '&'; *r++ = 'l'; *r++ = 't'; *r++ = ';';
                break;
            case '>':
                *r++ = '&'; *r++ = 'g'; *r++ = 't'; *r++ = ';';
                break;
            case '&':
                *r++ = '&'; *r++ = 'a'; *r++ = 'm'; *r++ = 'p'; *r++ = ';';
                break;
            default:
                *r++ = *s;
        }
    }

    *r = '\0';
    return result;
}

char* hello(const char *username) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "Hello %s", escape(username));
    return strdup(buffer);
}

void handle_request(const char *url) {
    const char *base = "/hello/";
    if (strncmp(url, base, strlen(base)) == 0) {
        const char *username = url + strlen(base);
        char *greeting = hello(username);
        printf("%s\n", greeting);
        free(greeting);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    handle_request("/hello/world");
    return 0;
}