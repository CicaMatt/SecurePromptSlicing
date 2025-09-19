#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 100

void escape(const char *src, char *dest) {
    while (*src) {
        if (*src == '<') {
            strcpy(dest, "&lt;");
            dest += 4;
        } else if (*src == '>') {
            strcpy(dest, "&gt;");
            dest += 4;
        } else if (*src == '&') {
            strcpy(dest, "&amp;");
            dest += 5;
        } else if (*src == '"') {
            strcpy(dest, "&quot;");
            dest += 6;
        } else if (*src == '\'') {
            strcpy(dest, "&#x27;");
            dest += 6;
        } else {
            *dest++ = *src;
        }
        src++;
    }
    *dest = '\0';
}

char* hello(const char *username) {
    static char result[256];
    char safe_username[MAX_USERNAME_LENGTH + 1];
    escape(username, safe_username);
    snprintf(result, sizeof(result), "Hello, %s!", safe_username);
    return result;
}

int main() {
    const char *username = "user&name";
    if (strcmp("/hello/user&name", "/hello/") == 0) {
        printf("URL does not include a username.\n");
    } else {
        printf("%s\n", hello(username));
    }
    return 0;
}