#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char* str) {
    int len = strlen(str);
    char* escaped_str = malloc(len * 6 + 1); // Max length if all chars are replaced
    int j = 0;
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '&': strcpy(&escaped_str[j], "&amp;"); j += 5; break;
            case '<': strcpy(&escaped_str[j], "&lt;"); j += 4; break;
            case '>': strcpy(&escaped_str[j], "&gt;"); j += 4; break;
            case '"': strcpy(&escaped_str[j], "&quot;"); j += 6; break;
            case '\'': strcpy(&escaped_str[j], "&#39;"); j += 5; break;
            default: escaped_str[j++] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello(const char* username) {
    char* escaped_username = escape(username);
    char* result = malloc(strlen(escaped_username) + 7); // "Hello " and "\n"
    sprintf(result, "Hello %s\n", escaped_username);
    free(escaped_username);
    return result;
}

int main() {
    const char* username = "test_user";
    char* greeting = hello(username);
    printf("%s", greeting);
    free(greeting);
    return 0;
}