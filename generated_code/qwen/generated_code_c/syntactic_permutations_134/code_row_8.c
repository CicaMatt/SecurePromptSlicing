#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char escaped_username[1024];
    escape(username, escaped_username);
    printf("Hello %s\n", escaped_username);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "/hello/") == 0 && argv[2] != NULL) {
        hello(argv[2]);
    } else {
        printf("Usage: ./program /hello/username\n");
    }
    return 0;
}