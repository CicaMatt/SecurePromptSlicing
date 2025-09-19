#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    int len = strlen(str);
    char *escaped_str = malloc(len * 6 + 1); // Each character could be up to 6 characters in HTML-safe sequence
    int j = 0;
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '&':
                strcpy(&escaped_str[j], "&amp;");
                j += 5;
                break;
            case '<':
                strcpy(&escaped_str[j], "&lt;");
                j += 4;
                break;
            case '>':
                strcpy(&escaped_str[j], "&gt;");
                j += 4;
                break;
            case '"':
                strcpy(&escaped_str[j], "&quot;");
                j += 6;
                break;
            case '\'':
                strcpy(&escaped_str[j], "&#39;");
                j += 5;
                break;
            default:
                escaped_str[j++] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    char *greeting = malloc(strlen(safe_username) + 7); // "Hello " and "\n"
    sprintf(greeting, "Hello %s\n", safe_username);
    free(safe_username);
    return greeting;
}

int main() {
    const char *username = "user&name";
    char *result = hello(username);
    printf("%s", result);
    free(result);
    return 0;
}