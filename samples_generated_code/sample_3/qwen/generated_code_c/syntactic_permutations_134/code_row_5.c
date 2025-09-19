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
        else *out++ = *str;
        str++;
    }
    *out = '\0';
}

void hello(char *username) {
    char safe_username[2*MAX_USERNAME_LENGTH + 1];
    escape(username, safe_username);
    printf("Hello %s\n", safe_username);
}

int main() {
    // Simulating navigation to /hello/username
    char username[MAX_USERNAME_LENGTH];
    strcpy(username, "user&name");
    
    if (strcmp("/hello/", "/hello/") == 0) { // This is a simplified check for demonstration
        hello(username);
    }
    
    return 0;
}