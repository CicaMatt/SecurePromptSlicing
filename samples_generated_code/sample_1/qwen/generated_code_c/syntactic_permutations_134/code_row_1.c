#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void escape(char *str, char *out) {
    while (*str) {
        switch (*str) {
            case '&': strcat(out, "&amp;"); break;
            case '<': strcat(out, "&lt;"); break;
            case '>': strcat(out, "&gt;"); break;
            case '"': strcat(out, "&quot;"); break;
            case '\'': strcat(out, "&#39;"); break;
            default: strncat(out, str, 1); break;
        }
        str++;
    }
}

void hello(char *username) {
    char safe_username[256] = {0};
    escape(username, safe_username);
    printf("Hello %s", safe_username);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/hello/") != 0) {
        fprintf(stderr, "Usage: %s /hello/ <username>\n", argv[0]);
        return 1;
    }
    hello(argv[2]);
    return 0;
}