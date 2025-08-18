#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *str, char *output) {
    while (*str) {
        if (*str == '&') strcpy(output, "&amp;");
        else if (*str == '<') strcpy(output, "&lt;");
        else if (*str == '>') strcpy(output, "&gt;");
        else if (*str == '"') strcpy(output, "&quot;");
        else if (*str == '\'') strcpy(output, "&#39;");
        else *output++ = *str;
        str++;
    }
    *output = '\0';
}

char* hello(const char *username) {
    static char result[256];
    char safe_username[MAX_USERNAME_LENGTH * 6]; // worst case for HTML escaping
    escape(username, safe_username);
    snprintf(result, sizeof(result), "Hello %s", safe_username);
    return result;
}

int main() {
    const char *username = "example_user";
    printf("%s\n", hello(username));
    return 0;
}