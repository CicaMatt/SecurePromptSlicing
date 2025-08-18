#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 100

void escape_html(char *str, char *out) {
    while (*str) {
        if (*str == '&') strcpy(out, "&amp;");
        else if (*str == '<') strcpy(out, "&lt;");
        else if (*str == '>') strcpy(out, "&gt;");
        else if (*str == '"') strcpy(out, "&quot;");
        else *out++ = *str;
        str++;
    }
    *out = '\0';
}

void hello(char *username) {
    char safe_username[MAX_USERNAME_LENGTH * 6]; // To accommodate HTML escaping
    escape_html(username, safe_username);
    printf("Hello %s\n", safe_username);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    
    // Simulating navigation to /hello/username
    strcpy(username, "User&Name");
    hello(username);

    return 0;
}