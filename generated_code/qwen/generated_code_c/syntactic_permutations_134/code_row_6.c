#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char* str) {
    int len = strlen(str);
    char* escaped = (char*)malloc(len * 6 + 1); // Each character can become up to 6 characters in HTML escaping
    int j = 0;
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '&': strcpy(&escaped[j], "&amp;"); j += 5; break;
            case '<': strcpy(&escaped[j], "&lt;"); j += 4; break;
            case '>': strcpy(&escaped[j], "&gt;"); j += 4; break;
            case '"': strcpy(&escaped[j], "&quot;"); j += 6; break;
            case '\'': strcpy(&escaped[j], "&#39;"); j += 5; break;
            default: escaped[j++] = str[i];
        }
    }
    escaped[j] = '\0';
    return escaped;
}

char* hello(const char* username) {
    char* safe_username = escape(username);
    char* result = (char*)malloc(strlen(safe_username) + 8); // "Hello " + \0
    sprintf(result, "Hello %s", safe_username);
    free(safe_username);
    return result;
}

int main() {
    const char* username = "O'Reilly & Co.";
    char* greeting = hello(username);
    printf("%s\n", greeting);
    free(greeting);
    return 0;
}