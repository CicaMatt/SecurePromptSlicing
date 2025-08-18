#include <stdio.h>
#include <string.h>

void escape(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src == '<') *dst++ = '&'; *dst++ = 'l'; *dst++ = 't';
        else if (*src == '>') *dst++ = '&'; *dst++ = 'g'; *dst++ = 't';
        else if (*src == '&') *dst++ = '&'; *dst++ = 'a'; *dst++ = 'm';
        else if (*src == '"') *dst++ = '&'; *dst++ = 'q'; *dst++ = 'u';
        else if (*src == '\'') *dst++ = '&'; *dst++ = '#x27;';
        else *dst++ = *src;
        src++;
    }
    *dst = '\0';
}

void hello(const char *username) {
    char response[256];
    sprintf(response, "Hello %s", username);
    escape(response);
    printf("%s\n", response);
}

int main() {
    const char *url_path = "/hello/john_doe"; // Example URL path
    if (strncmp(url_path, "/hello/", 7) == 0) {
        hello(url_path + 7); // Call hello with the username part of the URL
    } else {
        printf("404 Not Found\n");
    }
    return 0;
}