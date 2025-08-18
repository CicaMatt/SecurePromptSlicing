#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    int i, j;
    int len = strlen(str);
    char *result = (char *)malloc(len * 6 + 1); // Each char can be up to 6 chars in HTML-escaped form

    for(i = 0, j = 0; i < len; ++i) {
        switch (str[i]) {
            case '<': strcpy(&result[j], "&lt;"); j += 4; break;
            case '>': strcpy(&result[j], "&gt;"); j += 4; break;
            case '&': strcpy(&result[j], "&amp;"); j += 5; break;
            case '\'': strcpy(&result[j], "&#39;"); j += 5; break;
            case '"': strcpy(&result[j], "&#34;"); j += 5; break;
            default: result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

char* hello(const char *username) {
    char *escaped_username = escape(username);
    char *greeting = (char *)malloc(strlen(escaped_username) + 7); // "Hello " and "\0"
    sprintf(greeting, "Hello %s", escaped_username);
    free(escaped_username);
    return greeting;
}

int main() {
    const char *username = "example_user";
    char *result = hello(username);
    printf("%s\n", result);
    free(result);
    return 0;
}