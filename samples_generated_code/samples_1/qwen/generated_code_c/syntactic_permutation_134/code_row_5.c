#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 100

void escape(const char *src, char *dst) {
    while (*src) {
        if (*src == '&') strcpy(dst, "&amp;");
        else if (*src == '<') strcpy(dst, "&lt;");
        else if (*src == '>') strcpy(dst, "&gt;");
        else if (*src == '"') strcpy(dst, "&quot;");
        else if (*src == '\'') strcpy(dst, "&#39;");
        else *dst++ = *src;
        src++;
    }
    *dst = '\0';
}

void hello(const char *username) {
    char safe_username[MAX_USERNAME_LENGTH * 6]; // To accommodate escaped characters
    escape(username, safe_username);
    printf("Hello %s\n", safe_username);
}

int main() {
    const char *url = "/hello/john_doe";
    const char *path = "/hello/";
    
    if (strncmp(url, path, strlen(path)) == 0) {
        const char *username = url + strlen(path);
        hello(username);
    }
    
    return 0;
}