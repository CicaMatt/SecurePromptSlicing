#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *str, char *out) {
    while (*str) {
        if (*str == '&') strcpy(out, "&amp;");
        else if (*str == '<') strcpy(out, "&lt;");
        else if (*str == '>') strcpy(out, "&gt;");
        else if (*str == '"') strcpy(out, "&quot;");
        else if (*str == '\'') strcpy(out, "&#39;");
        else *out++ = *str;
        str++;
    }
    *out = '\0';
}

void hello(char *username) {
    char escaped_username[MAX_USERNAME_LENGTH * 6 + 1]; // Maximum length considering HTML escaping
    escape(username, escaped_username);
    printf("Hello %s", escaped_username);
}

int main() {
    // Simulating navigation to /hello/username
    char username[] = "User&Name";
    hello(username);
    return 0;
}